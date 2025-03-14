#include "VkpDevice.h"

#include <iostream>
#include <vector>
#include <stdexcept>

namespace vkp {

VkpDevice::VkpDevice(VkSurfaceKHR windowSurface, std::vector<const char*> deviceExtensions): enabledDeviceExtensions(deviceExtensions), surface(windowSurface)
{

}


VkpDevice::~VkpDevice()
{

}

void VkpDevice::Init(VkInstance instance)
{
  PickPhysicalDevice(instance);
  CreateLogicalDevice();
}

void VkpDevice::PickPhysicalDevice(VkInstance instance)
{
  uint32_t deviceCount = 0;
  vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

  if(deviceCount == 0)
  {
    throw std::runtime_error("Failed to find GPUs with Vulkan support!");
  }

  std::vector<VkPhysicalDevice> devices(deviceCount);
  vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

  for (const auto& device : devices) 
  {
    if (IsDeviceSuitable(device)) 
    {
      physicalDevice = device;
      break;
    }
  }

  if (physicalDevice == VK_NULL_HANDLE) 
  {
    throw std::runtime_error("failed to find a suitable GPU!");
  }

  VkPhysicalDeviceProperties deviceProperties;
  vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);

  std::cout << "Physical device initialised." << std::endl;
  std::cout << deviceProperties.deviceName << std::endl; 
}

void VkpDevice::CreateLogicalDevice()
{
  QueueFamilyIndices queueFamilyIndices = FindQueueFamilies(physicalDevice);
    
  std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
  auto uniqueQueueFamilies = queueFamilyIndices.ToSet();
  
  float queuePriority = 1.0f;

  for (uint32_t queueFamily : uniqueQueueFamilies) 
  {
    VkDeviceQueueCreateInfo queueCreateInfo{};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = queueFamily;
    queueCreateInfo.queueCount = 1;
    queueCreateInfo.pQueuePriorities = &queuePriority;
    queueCreateInfos.push_back(queueCreateInfo);
  }


  VkPhysicalDeviceFeatures deviceFeatures{};


  VkDeviceCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

  createInfo.pQueueCreateInfos = queueCreateInfos.data();
  createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());;
  
  createInfo.pEnabledFeatures = &deviceFeatures;

  createInfo.enabledExtensionCount = static_cast<uint32_t>(enabledDeviceExtensions.size());
  createInfo.ppEnabledExtensionNames = enabledDeviceExtensions.data();

  
  if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) 
  {
    throw std::runtime_error("failed to create logical device!");
  }
  
  vkGetDeviceQueue(device, queueFamilyIndices.presentFamily.value(), 0, &presentQueue);
  vkGetDeviceQueue(device, queueFamilyIndices.graphicsFamily.value(), 0, &graphicsQueue);
}


void VkpDevice::Cleanup()
{
  vkDestroyDevice(device, nullptr);
}

bool VkpDevice::IsDeviceSuitable(VkPhysicalDevice device)
{
  QueueFamilyIndices indices = FindQueueFamilies(device);
  bool extensionsSupported = CheckDeviceExtensionSupport(device);

  bool swapChainAdequate = false;
  if (extensionsSupported) 
  {
      SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport(device);
      swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
  }

  return indices.IsComplete() && extensionsSupported && swapChainAdequate;
}

bool VkpDevice::CheckDeviceExtensionSupport(VkPhysicalDevice device)
{
  uint32_t extensionCount;
  vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

  std::vector<VkExtensionProperties> availableExtensions(extensionCount);
  vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

  std::set<std::string> requiredExtensions(enabledDeviceExtensions.begin(), enabledDeviceExtensions.end());

  for (const auto& extension : availableExtensions) 
  {
    //std::cout << "Extension: " << extension.extensionName << "available" << std::endl;
    requiredExtensions.erase(extension.extensionName);
  }

  return requiredExtensions.empty();
}

QueueFamilyIndices VkpDevice::FindQueueFamilies(VkPhysicalDevice device)
{
  uint32_t queueFamilyCount;
  vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

  std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
  vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

  QueueFamilyIndices indices;

  uint32_t i = 0;
  VkBool32 presentSupport = false;
  for(const auto& queueFamily : queueFamilies)
  {
    if(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
    {
      indices.graphicsFamily = i;
    }

    vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
    if (presentSupport) 
    {
      indices.presentFamily = i;
    }

    if (indices.IsComplete()) 
    {
      break;
    } 

    i++;
  }

  return indices;
}

SwapChainSupportDetails VkpDevice::QuerySwapChainSupport(VkPhysicalDevice device)
{
  SwapChainSupportDetails details;

  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

  uint32_t formatCount;
  vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);
  
  if (formatCount != 0)
  {
    details.formats.resize(formatCount);
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
  }

  uint32_t presentModeCount;
  vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);
  
  if (presentModeCount != 0) 
  {
    details.presentModes.resize(presentModeCount);
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
  }

  return details;
}

} // namespace vkp