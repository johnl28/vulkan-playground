#include "VKPlayground.h"

#include <cstring>
#include <string>
#include <iostream>
#include <vector>

#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>


#include "constants.h"

namespace vkp 
{
  const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
  };

  static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData) 
    {

    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

    return VK_FALSE;
  }

  VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) 
  {
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr) 
    {
      return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    } 
    else 
    {
      return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
  }

  void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) 
  {
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) 
    {
      func(instance, debugMessenger, pAllocator);
    }
  }

  VKApp::VKApp()
  {
    InitApp();
  }

  void VKApp::InitApp()
  {
    InitWindow();
    InitVulkan();
    InitDebugMessenger();
    PickPhysicalDevice();
    CreateLogicalDevice();
  }

  void VKApp::InitWindow()
  {

    glfwInit();
    
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Vulkan", nullptr, nullptr);

    
  
    std::cout << "Window initialised!" << std::endl;
  }

  void VKApp::InitVulkan()
  {
    CreateInstance();
  }

  void VKApp::CreateInstance()
  {

    if(enableValidationLayers && !CheckValidationLayersSupport())
    {
      throw std::runtime_error("Required validation layers are not available.");
    }
    else if(enableValidationLayers)
    {
      std::cout << "Validation layers enabled." << std::endl;
    }

    VkApplicationInfo vkInfo{};
    vkInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    vkInfo.pApplicationName = "Hello Vulkan";
    vkInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    vkInfo.pEngineName = "No Engine";
    vkInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    vkInfo.apiVersion = VK_API_VERSION_1_0;


    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &vkInfo;


    auto extensions = GetRequiredExtensions();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

    if(enableValidationLayers)
    {
      createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
      createInfo.ppEnabledLayerNames = validationLayers.data();
    }
    else 
    { 
      createInfo.enabledLayerCount = 0;
    }
  
    if(vkCreateInstance(&createInfo, nullptr, &vkInstance) != VK_SUCCESS)
    {
      throw std::runtime_error("Failed to create Vulkan instance");
    }
    
    std::cout << "Vulkan instance created." << std::endl;
  }

  void VKApp::PickPhysicalDevice()
  {
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(vkInstance, &deviceCount, nullptr);

    if(deviceCount == 0)
    {
      throw std::runtime_error("Failed to find GPUs with Vulkan support!");
    }


    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(vkInstance, &deviceCount, devices.data());

    for (const auto& device : devices) {
      if (IsDeviceSuitable(device)) 
      {
          vkPhysicalDevice = device;
          break;
      }
    }
  
    if (vkPhysicalDevice == VK_NULL_HANDLE) {
      throw std::runtime_error("failed to find a suitable GPU!");
    }

    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(vkPhysicalDevice, &deviceProperties);


    std::cout << "Physical device initialised." << std::endl;
    std::cout << deviceProperties.deviceName << std::endl; 
  }

  void VKApp::InitDebugMessenger()
  {
    if(!enableValidationLayers) return;

    VkDebugUtilsMessengerCreateInfoEXT createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo.pfnUserCallback = DebugCallback;
    createInfo.pUserData = nullptr; // Optional

    if (CreateDebugUtilsMessengerEXT(vkInstance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
      throw std::runtime_error("failed to set up debug messenger!");
    }

    std::cout << "Debug callback initialised" << std::endl;
  }

  void VKApp::CreateLogicalDevice()
  {
    QueueFamilyIndices queueFamilyIndices = FindQueueFamilies(vkPhysicalDevice);
    
    VkDeviceQueueCreateInfo queueCreateInfo{};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();
    queueCreateInfo.queueCount = 1;

    float queuePriority = 1.0f;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    VkPhysicalDeviceFeatures deviceFeatures{};

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

    createInfo.pQueueCreateInfos = &queueCreateInfo;
    createInfo.queueCreateInfoCount = 1;
    
    createInfo.pEnabledFeatures = &deviceFeatures;

    createInfo.enabledExtensionCount = 0;

    if (vkCreateDevice(vkPhysicalDevice, &createInfo, nullptr, &vkDevice) != VK_SUCCESS) {
      throw std::runtime_error("failed to create logical device!");
    }

  }

  std::vector<const char *> VKApp::GetRequiredExtensions()
  {
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

    if(enableValidationLayers)
    {
      extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    return extensions;
  }

  QueueFamilyIndices VKApp::FindQueueFamilies(VkPhysicalDevice device)
  {
    uint32_t queueFamilyCount;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    QueueFamilyIndices indices;

    uint32_t i = 0;
    for(const auto& queueFamily : queueFamilies)
    {
      if(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
      {
        indices.graphicsFamily = i;
      }

      if (indices.IsComplete()) 
      {
        break;
      } 

      i++;
    }

    return indices;
  }

  bool VKApp::CheckValidationLayersSupport()
  {

    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);

    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());


    for (const char* layerName : validationLayers) 
    {
      bool layerFound = false;

      for (const auto& layerProperties : availableLayers) 
      {
        if (strcmp(layerName, layerProperties.layerName) == 0) 
        {
          layerFound = true;
          break;
        }
      }

      if (!layerFound) 
      {
        return false;
      }

    }

    return true;
  }

  bool VKApp::IsDeviceSuitable(VkPhysicalDevice device)
  {
    QueueFamilyIndices indices = FindQueueFamilies(device);

    return indices.IsComplete();
  }

  void VKApp::Cleanup()
  {
    vkDestroyDevice(vkDevice, nullptr);

    if (enableValidationLayers) 
    {
      DestroyDebugUtilsMessengerEXT(vkInstance, debugMessenger, nullptr);
    }

    vkDestroyInstance(vkInstance, nullptr);

    glfwDestroyWindow(glfwWindow);

    glfwTerminate();
  }

  void VKApp::Run()
  {

    while(!glfwWindowShouldClose(glfwWindow)) 
    {
      glfwPollEvents();
    }
  }

}