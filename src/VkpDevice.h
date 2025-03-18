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

      QueueFamilyIndices GetQueueFamilies() { return FindQueueFamilies(physicalDevice); }
      uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) ;

      void Init(VkInstance instance);
      void Cleanup();

      const VkPhysicalDeviceProperties& GetPhysicalDeviceProps();

      std::string GetDeviceName() { return GetPhysicalDeviceProps().deviceName; }
      std::string GetDeviceTypeName();
      
      
    private:
      void PickPhysicalDevice(VkInstance instance);
      void CreateLogicalDevice();
      bool IsDeviceSuitable(VkPhysicalDevice device);
      bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
    
      QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
      SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
      
    private:
      VkPhysicalDeviceProperties deviceProperties{};

      std::vector<const char*> enabledDeviceExtensions;

      VkSurfaceKHR surface = VK_NULL_HANDLE;
      VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
      VkDevice device = VK_NULL_HANDLE;

      VkQueue presentQueue = VK_NULL_HANDLE;
      VkQueue graphicsQueue = VK_NULL_HANDLE;
  };
}


