
#include "VkpSwapchain.h"
#include "VkpCore.h"

#include <algorithm>


namespace vkp {



VkpSwapchain::VkpSwapchain(VkDevice _device, VkSurfaceKHR _surface): surface(_surface), device(_device)
{

}

VkpSwapchain::~VkpSwapchain()
{

}

void VkpSwapchain::Init(VkPhysicalDevice physicalDevice, QueueFamilyIndices queueFamilyInidices, VkExtent2D prefferedExtent)
{
  SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport(physicalDevice);

  VkSurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat(swapChainSupport.formats);
  VkPresentModeKHR presentMode = ChooseSwapPresentMode(swapChainSupport.presentModes);
  VkExtent2D extent = ChooseSwapExtent(swapChainSupport.capabilities, prefferedExtent);

  uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
  if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) 
  {
    imageCount = swapChainSupport.capabilities.maxImageCount;
  }

  swapChainImageFormat = surfaceFormat.format;
  swapChainExtent = extent;

  VkSwapchainCreateInfoKHR createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
  createInfo.surface = surface;
  createInfo.minImageCount = imageCount;
  createInfo.imageFormat = surfaceFormat.format;
  createInfo.imageColorSpace = surfaceFormat.colorSpace;
  createInfo.imageExtent = extent;
  createInfo.imageArrayLayers = 1;
  createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
  createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
  createInfo.presentMode = presentMode;
  createInfo.clipped = VK_TRUE;
  createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
  createInfo.oldSwapchain = VK_NULL_HANDLE;

  uint32_t queueFamilyIndicesArr[] = {queueFamilyInidices.graphicsFamily.value(), queueFamilyInidices.presentFamily.value()};
  
  if (queueFamilyInidices.graphicsFamily != queueFamilyInidices.presentFamily) 
  {
    createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
    createInfo.queueFamilyIndexCount = 2;
    createInfo.pQueueFamilyIndices = queueFamilyIndicesArr;
  } 
  else 
  {
    createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    createInfo.queueFamilyIndexCount = 0; // Optional
    createInfo.pQueueFamilyIndices = nullptr; // Optional
  }

  if (vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapChain) != VK_SUCCESS) 
  {
    throw std::runtime_error("failed to create swap chain!");
  }

  vkGetSwapchainImagesKHR(device, swapChain, &imageCount, nullptr);
  swapChainImages.resize(imageCount);
  vkGetSwapchainImagesKHR(device, swapChain, &imageCount, swapChainImages.data());

  CreateImageViews();
}

void VkpSwapchain::CreateImageViews()
{
  swapChainImageViews.resize(swapChainImages.size());

  for (size_t i = 0; i < swapChainImages.size(); i++) 
  {
    VkImageViewCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    createInfo.image = swapChainImages[i];
    createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    createInfo.format = swapChainImageFormat;

    createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

    createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    createInfo.subresourceRange.baseMipLevel = 0;
    createInfo.subresourceRange.levelCount = 1;
    createInfo.subresourceRange.baseArrayLayer = 0;
    createInfo.subresourceRange.layerCount = 1;

    if (vkCreateImageView(device, &createInfo, nullptr, &swapChainImageViews[i]) != VK_SUCCESS) 
    {
      throw std::runtime_error("failed to create image views!");
    }
  }
}

void VkpSwapchain::Cleanup()
{
  for (auto imageView : swapChainImageViews) 
  {
    vkDestroyImageView(device, imageView, nullptr);
  }

  vkDestroySwapchainKHR(device, swapChain, nullptr);
}

VkSurfaceFormatKHR VkpSwapchain::ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats)
{
  for (const auto& availableFormat : availableFormats) 
  {
    if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) 
    {
      return availableFormat;
    }
  }

  return availableFormats[0];
}

VkPresentModeKHR VkpSwapchain::ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes) 
{
  for (const auto& availablePresentMode : availablePresentModes) 
  {
    if (availablePresentMode == VK_PRESENT_MODE_FIFO_KHR) 
    {
      return availablePresentMode;
    }
  }

  return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D VkpSwapchain::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, VkExtent2D actualExtent) 
{
  if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) 
  {
    return capabilities.currentExtent;
  } 
  else 
  {
    actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
    actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

    return actualExtent;
  }
}

SwapChainSupportDetails VkpSwapchain::QuerySwapChainSupport(VkPhysicalDevice device)
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
