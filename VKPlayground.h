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
      void InitWindow();
      void InitVulkan();
      void CreateInstance();

      void InitApp();
      void Cleanup();

    private:
      GLFWwindow *glfwWindow;
      VkInstance vkInstance;
  };

}

