#include "VKPlayground.h"

#include <cstring>
#include <string>
#include <iostream>
#include <vector>

#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>


#include "constants.h"

namespace vkp 
{
  const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
  };

  VKApp::VKApp()
  {
    InitApp();
  }

  void VKApp::InitApp()
  {
    InitWindow();
    InitVulkan();
    PickPhysicalDevice();
  }

  void VKApp::InitWindow()
  {

    glfwInit();
    
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Vulkan", nullptr, nullptr);

    
  
    std::cout << "Window initialised!" << std::endl;
  }

  void VKApp::InitVulkan()
  {
    CreateInstance();
  }

  void VKApp::CreateInstance()
  {

    if(enableValidationLayers && !CheckValidationLayersSupport())
    {
      throw std::runtime_error("Required validation layers are not available.");
    }
    else if(enableValidationLayers)
    {
      std::cout << "Validation layers enabled." << std::endl;
    }

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


    auto extensions = GetRequiredExtensions();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

    if(enableValidationLayers)
    {
      createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
      createInfo.ppEnabledLayerNames = validationLayers.data();
    }
    else 
    { 
      createInfo.enabledLayerCount = 0;
    }
  
    if(vkCreateInstance(&createInfo, nullptr, &vkInstance) != VK_SUCCESS)
    {
      throw std::runtime_error("Failed to create Vulkan instance");
    }
    
    std::cout << "Vulkan instance created." << std::endl;
  }

  void VKApp::PickPhysicalDevice()
  {
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(vkInstance, &deviceCount, nullptr);

    if(deviceCount == 0)
    {
      throw std::runtime_error("Failed to find GPUs with Vulkan support!");
    }


    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(vkInstance, &deviceCount, devices.data());

    for (const auto& device : devices) {
      if (IsDeviceSuitable(device)) 
      {
          vkDevice = device;
          break;
      }
    }
  
    if (vkDevice == VK_NULL_HANDLE) {
      throw std::runtime_error("failed to find a suitable GPU!");
    }

    std::cout << "Physical device initialised." << std::endl;
  }

  std::vector<const char *> VKApp::GetRequiredExtensions()
  {
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

    if(enableValidationLayers)
    {
      extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    return extensions;
  }

  bool VKApp::CheckValidationLayersSupport()
  {

    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);

    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());


    for (const char* layerName : validationLayers) 
    {
      bool layerFound = false;

      for (const auto& layerProperties : availableLayers) 
      {
        if (strcmp(layerName, layerProperties.layerName) == 0) 
        {
          layerFound = true;
          break;
        }
      }

      if (!layerFound) 
      {
        return false;
      }

    }

    return true;
  }

  bool VKApp::IsDeviceSuitable(VkPhysicalDevice device)
  {

    return true;
  }

  void VKApp::Cleanup()
  {
    vkDestroyInstance(vkInstance, nullptr);

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