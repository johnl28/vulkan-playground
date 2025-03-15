#pragma once

#include "vulkan/vulkan.h"

namespace vkp {

  class VkpRenderPass 
  {
    public:
      VkpRenderPass(VkDevice _device);
      ~VkpRenderPass();

      void Init(VkFormat format);
      void Cleanup();
      VkRenderPass GetHandle() const { return renderPass; }

    private:
      VkRenderPass renderPass;
      VkDevice device;
  };

} // namespace vkp


