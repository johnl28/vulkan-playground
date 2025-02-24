#pragma once

#include <set>
#include <vector>
#include <optional>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "Utils.h"


namespace vkp 
{
  struct QueueFamilyIndices 
  {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool IsComplete()
    {
      return graphicsFamily.has_value() && presentFamily.has_value();
    }

    std::set<uint32_t> ToSet() 
    {
      return {  
        graphicsFamily.value(), 
        presentFamily.value()
      };
    }
  };

  struct SwapChainSupportDetails 
  {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
  };

} 