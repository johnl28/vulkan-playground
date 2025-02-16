#include "VKPlayground.h"

#include <iostream>

#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>


#include "constants.h"

namespace vkp 
{

  VKApp::VKApp()
  {
    InitApp();
  }

  void VKApp::InitApp()
  {
    InitWindow();
    InitVulkan();
  }

  void VKApp::InitWindow()
  {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Vulkan", nullptr, nullptr);
  }

  void VKApp::InitVulkan()
  {
    CreateInstance();
  }

  void VKApp::CreateInstance()
  {
    VkApplicationInfo vkInfo{};
    vkInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    vkInfo.pApplicationName = "Hello Triangle";
    vkInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    vkInfo.pEngineName = "No Engine";
    vkInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    vkInfo.apiVersion = VK_API_VERSION_1_0;


    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &vkInfo;

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    
    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    createInfo.enabledLayerCount = 0;

    if(vkCreateInstance(&createInfo, nullptr, &vkInstance) != VK_SUCCESS)
    {
      throw std::runtime_error("Failed to create Vulkan instance");
    }
    
  }

  void VKApp::Cleanup()
  {
    glfwDestroyWindow(glfwWindow);

    glfwTerminate();
  }

  void VKApp::Run()
  {

    while(!glfwWindowShouldClose(glfwWindow)) 
    {
      glfwPollEvents();
    }
  }

}