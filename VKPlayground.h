#pragma once

#include <vector>
#include <optional>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>




namespace vkp 
{

  struct QueueFamilyIndices 
  {
    std::optional<uint32_t> graphicsFamily;

    bool IsComplete()
    {
      return graphicsFamily.has_value();
    }
  };

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
      void InitDebugMessenger();
      void CreateLogicalDevice();

      QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

      std::vector<const char*> GetRequiredExtensions();
      bool CheckValidationLayersSupport();
      bool IsDeviceSuitable(VkPhysicalDevice device);

      void InitApp();
      void Cleanup();

    private:
      GLFWwindow *glfwWindow;
      VkInstance vkInstance;
      VkDebugUtilsMessengerEXT debugMessenger;
      VkPhysicalDevice vkPhysicalDevice = VK_NULL_HANDLE;
      VkDevice vkDevice = VK_NULL_HANDLE;

      VkQueue graphicsQueue;
  };

}

