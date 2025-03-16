#pragma once
#include <filesystem>
#include <vector>

#include "vulkan/vulkan.h"

#include "VkpCore.h"
#include "VkpSwapchain.h"

namespace vkp {
  struct PipelineInit 
  {
    VkpFilePath VertexShaderFile;
    VkpFilePath FragmentShaderFile;
    VkViewport Viewport;
    VkRect2D Scissor;

    VkRenderPass RenderPassHandle;
    VkDescriptorSetLayout DescriptorSetLayout;
  };


  class VkpPipeline 
  {
    public:
      VkpPipeline(VkDevice deviceHandle);
      ~VkpPipeline();

      void Init(PipelineInit initData);
      void Cleanup();

      VkPipeline GetHandle() const { return graphicsPipeline; }
      VkPipelineLayout GetLayout() const { return pipelineLayout; }

    private:
      VkShaderModule LoadShaderModule(const VkpFilePath &shaderPath);
      VkShaderModule CreateShaderModule(const std::vector<char> &code);


    private:
      VkDevice device;

      VkPipelineLayout pipelineLayout;
      VkPipeline graphicsPipeline;
  };

}


