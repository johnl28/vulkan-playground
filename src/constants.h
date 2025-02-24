#pragma once

namespace vkp {
  constexpr int WINDOW_WIDTH = 800;
  constexpr int WINDOW_HEIGHT = 600;

#ifdef NDEBUG
  constexpr bool enableValidationLayers = false;
#else
  constexpr bool enableValidationLayers = true;
#endif

}



