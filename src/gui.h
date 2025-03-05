#pragma once
#include "VKCore.h"


namespace vkp
{
  struct GuiInitInfo 
  {
    GLFWwindow* window;
    VkInstance instance;
    VkPhysicalDevice physicalDevice;
    VkDevice device;
    uint32_t queueFamily;
    VkQueue queue;
    VkPipelineCache pipelineCache;
    VkDescriptorPool descriptorPool;
    VkRenderPass renderPass;
    uint32_t minImageCount;
    uint32_t imageCount;
    VkSampleCountFlagBits msaaSamples;
    VkAllocationCallbacks* allocator;
    void (*checkVkResultFn)(VkResult, const char*);
  };

  class GUI 
  {
    public:
      GUI() {};
      ~GUI() {};

      void Init(GuiInitInfo initInfo);
      void Render(VkCommandBuffer commandBuffer);
      void Cleanup();

  };
}
