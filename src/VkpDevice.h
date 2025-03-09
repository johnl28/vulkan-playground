#pragma once
#include "VkpCore.h"

#include "vulkan/vulkan.h"

namespace vkp {

  class VkpDevice 
  {
    public:
      VkpDevice(VkSurfaceKHR surface, std::vector<const char*> requiredDeviceExtensions);
      ~VkpDevice();

      VkPhysicalDevice GetPhysicalDevice() const { return physicalDevice; }
      VkDevice GetDevice() const { return device; }

      VkQueue GetPresentQueue() const { return presentQueue; }
      VkQueue GetGraphicsQueue() const { return graphicsQueue; }

      void PickPhysicalDevice(VkInstance instance);
      void CreateLogicalDevice();

      void Cleanup();

      QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

    private:
      bool IsDeviceSuitable(VkPhysicalDevice device);
      bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
      
      SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);

    private:
      std::vector<const char*> enabledDeviceExtensions;

      VkSurfaceKHR surface = VK_NULL_HANDLE;
      VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
      VkDevice device = VK_NULL_HANDLE;

      VkQueue presentQueue = VK_NULL_HANDLE;
      VkQueue graphicsQueue = VK_NULL_HANDLE;
  };
}


