#pragma once

#include <memory>

#include "VkpCore.h"
#include "gui.h"

#include "VkpDevice.h"
#include "VkpSwapchain.h"
#include "VkpRenderPass.h"
#include "VkpPipeline.h"

namespace vkp 
{

  class VkpApp 
  {
    public:
      VkpApp();
      void Run();
      void Cleanup();


    protected:
      void InitWindow();
      void InitVulkan();
      void CreateInstance();
      void CreateSurface();
      void InitDevice();
      void InitDebugMessenger();
      void InitSwapchain();
      void CreateFramebuffers();
      void InitRenderPass();

      void CreateDescriptorSetLayout();
      void InitGraphicsPipeline();
      void CreateCommandPool();
      void CreateVertexBuffer();
      void CreateIndexBuffer();
      void CreateCommandBuffers();
      void CreateSyncObjects();

      void CreateUniformBuffers();
      void CreateDescriptorPool();
      void CreateDescriptorSets();

      void UpdateUniformBuffer(uint32_t currentImage);
      void RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
      void DrawFrame();
      
      
      std::vector<const char*> GetRequiredExtensions();
      bool CheckValidationLayersSupport();



      
      VkRect2D GetScissor(int32_t x = 0, int32_t y = 0); 
      VkViewport GetViewport();

      void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
      void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

      void CleanupVulkan();

      void InitApp();
      void InitGUI();

    private:
      uint32_t currentFrame = 0;

      std::unique_ptr<VkpDevice> device;
      std::unique_ptr<VkpSwapchain> swapchain;
      std::unique_ptr<VkpRenderPass> renderPass;
      std::unique_ptr<VkpPipeline> pipeline;

      GLFWwindow *glfwWindow;
      VkInstance vkInstance;
      VkDebugUtilsMessengerEXT debugMessenger;

      VkPhysicalDevice vkPhysicalDevice = VK_NULL_HANDLE;
      VkDevice vkDevice = VK_NULL_HANDLE;

      VkQueue graphicsQueue;
      VkSurfaceKHR surface;

      std::vector<VkFramebuffer> swapChainFramebuffers;
      std::vector<VkCommandBuffer> commandBuffers;


      VkCommandPool commandPool;
      VkDescriptorPool descriptorPool;

      VkBuffer vertexBuffer;
      VkDeviceMemory vertexBufferMemory;

      VkBuffer indexBuffer;
      VkDeviceMemory indexBufferMemory;

      VkDescriptorSetLayout descriptorSetLayout;
      std::vector<VkDescriptorSet> descriptorSets;

      std::vector<VkBuffer> uniformBuffers;
      std::vector<VkDeviceMemory> uniformBuffersMemory;
      std::vector<void*> uniformBuffersMapped;

      std::vector<VkSemaphore> imageAvailableSemaphores;
      std::vector<VkSemaphore> renderFinishedSemaphores;
      std::vector<VkFence> inFlightFences;

      GUI gui;

  };


}
