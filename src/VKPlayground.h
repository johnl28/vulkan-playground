#pragma once

#include "VKCore.h"


namespace vkp 
{

  class VKApp 
  {
    public:
      VKApp();
      void Run();
      void Cleanup();


    protected:
      void InitWindow();
      void InitVulkan();
      void CreateInstance();
      void CreateSurface();
      void PickPhysicalDevice();
      void InitDebugMessenger();
      void CreateLogicalDevice();
      void CreateSwapChain();
      void CreateImageViews();
      void CreateRenderPass();
      void CreateGraphicsPipeline();
      void CreateFramebuffers();
      void CreateCommandPool();
      void CreateCommandBuffer();
      void CreateSyncObjects();

      void RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
      void DrawFrame();
      
      QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
      
      std::vector<const char*> GetRequiredExtensions();
      bool CheckValidationLayersSupport();
      bool IsDeviceSuitable(VkPhysicalDevice device);
      bool CheckDeviceExtensionSupport(VkPhysicalDevice device);

      SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
      VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
      VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
      VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);

      VkShaderModule CreateShaderModule(const std::vector<char>& code);

      void InitApp();

    private:
      GLFWwindow *glfwWindow;
      VkInstance vkInstance;
      VkDebugUtilsMessengerEXT debugMessenger;
      VkPhysicalDevice vkPhysicalDevice = VK_NULL_HANDLE;
      VkDevice vkDevice = VK_NULL_HANDLE;

      VkQueue graphicsQueue;
      VkQueue presentQueue;
      VkSurfaceKHR surface;
      VkSwapchainKHR swapChain;

      std::vector<VkFramebuffer> swapChainFramebuffers;
      std::vector<VkImageView> swapChainImageViews;
      std::vector<VkImage> swapChainImages;
      VkFormat swapChainImageFormat;
      VkExtent2D swapChainExtent;
      VkRenderPass renderPass;
      VkPipelineLayout pipelineLayout;
      VkPipeline graphicsPipeline;
      VkCommandPool commandPool;
      VkCommandBuffer commandBuffer;


      VkSemaphore imageAvailableSemaphore;
      VkSemaphore renderFinishedSemaphore;
      VkFence inFlightFence;
  };


}
