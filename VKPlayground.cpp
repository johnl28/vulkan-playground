#include "VKPlayground.h"

#include <iostream>

#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

namespace vkp 
{

  VKApp::VKApp()
  {
    InitApp();
  }

  void VKApp::InitApp()
  {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindow = glfwCreateWindow(800, 600, "Vulkan window", nullptr, nullptr);

    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
  
    std::cout << extensionCount << " extensions supported\n";
  
    glm::mat4 matrix;
    glm::vec4 vec;
    auto test = matrix * vec;    
  }

  void VKApp::Run()
  {

    while(!glfwWindowShouldClose(glfwWindow)) 
    {
      glfwPollEvents();
    }

    glfwDestroyWindow(glfwWindow);

    glfwTerminate();
  }

}