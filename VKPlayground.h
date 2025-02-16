#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>


namespace vkp 
{

  class VKApp 
  {
    public:
      VKApp();
      void Run();


    protected:
      void InitApp();

    private:
      GLFWwindow *glfwWindow = nullptr;
  };

}

