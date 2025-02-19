#pragma once

namespace vkp {
  const constexpr int WINDOW_WIDTH = 800;
  const constexpr int WINDOW_HEIGHT = 600;


#ifdef NDEBUG
  const bool enableValidationLayers = false;
#else
  const bool enableValidationLayers = true;
#endif

}



