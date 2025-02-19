#pragma once

#include <vector>

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
      void PickPhysicalDevice();

      std::vector<const char*> GetRequiredExtensions();
      bool CheckValidationLayersSupport();
      bool IsDeviceSuitable(VkPhysicalDevice device);

      void InitApp();
      void Cleanup();

    private:
      GLFWwindow *glfwWindow;
      VkInstance vkInstance;
      VkPhysicalDevice vkDevice = VK_NULL_HANDLE;
  };

}

