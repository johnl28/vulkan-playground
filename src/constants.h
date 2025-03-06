#pragma once

namespace vkp {
  constexpr int WINDOW_WIDTH = 800;
  constexpr int WINDOW_HEIGHT = 600;
  constexpr int MAX_FRAMES_IN_FLIGHT = 2;

#ifdef NDEBUG
  constexpr bool enableValidationLayers = false;
#else
  constexpr bool enableValidationLayers = true;
#endif
}



