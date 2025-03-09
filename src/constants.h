#pragma once
#include <vector>


namespace vkp {
  constexpr int WINDOW_WIDTH = 800;
  constexpr int WINDOW_HEIGHT = 600;
  constexpr int MAX_FRAMES_IN_FLIGHT = 2;

#ifdef NDEBUG
  constexpr bool enableValidationLayers = false;
#else
  constexpr bool enableValidationLayers = true;
#endif

  inline const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
  };

  inline const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
  };


}



