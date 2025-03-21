#pragma once
#include "VkpCore.h"

#include "vulkan/vulkan.h"

#include <vector>

namespace vkp {

  class VkpSwapchain
  {
    public:
      VkpSwapchain(VkDevice _device, VkSurfaceKHR _surface);
      ~VkpSwapchain();

      void Init(VkPhysicalDevice physicalDevice, QueueFamilyIndices queueFamilyInidices, VkExtent2D prefferedExtent);
      void Cleanup();

      VkSwapchainKHR GetHandle() const { return swapChain;}
      VkFormat GetImageFormat() const {return swapChainImageFormat; }

      const VkExtent2D& GetExtent() const { return swapChainExtent; }
      
      
      const std::vector<VkImageView> &GetImageViews() const { return swapChainImageViews; }
      const std::vector<VkImage> &GetImages() const { return swapChainImages; }

    private:
      SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
      VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
      VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
      VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities, VkExtent2D actualExtent);

      void CreateImageViews();

    private:
      VkSurfaceKHR surface;
      VkDevice device;

      VkSwapchainKHR swapChain;

      VkFormat swapChainImageFormat;
      VkExtent2D swapChainExtent;

      std::vector<VkImageView> swapChainImageViews;
      std::vector<VkImage> swapChainImages;
  };

}


