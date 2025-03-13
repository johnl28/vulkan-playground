#pragma once
#include "vulkan/vulkan.h"

#include <vector>

namespace vkp {

  class VkpSwapchain
  {
    public:
      VkpSwapchain(VkSurfaceKHR _surface);
      ~VkpSwapchain();

      void InitSwapchain(VkPhysicalDevice physicalDevice, QueueFamilyIndices queueFamilyInidices, VkDevice device, VkExtent2D extent);

      VkSwapchainKHR GetHandle() const { return swapChain;}
      VkExtent2D GetExtent() const { return swapChainExtent; }

      const std::vector<VkFramebuffer> &GetFrameBuffers() const { return swapChainFramebuffers; }
      const std::vector<VkImageView> &GetImageViews() const { return swapChainImageViews; }
      const std::vector<VkImage> &GetImages() const { return swapChainImages; }

    private:
      SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
      VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
      VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
      VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities, VkExtent2D actualExtent);


    private:
      VkSurfaceKHR surface;

      VkSwapchainKHR swapChain;

      VkFormat swapChainImageFormat;
      VkExtent2D swapChainExtent;

      std::vector<VkFramebuffer> swapChainFramebuffers;
      std::vector<VkImageView> swapChainImageViews;
      std::vector<VkImage> swapChainImages;
  };

}


