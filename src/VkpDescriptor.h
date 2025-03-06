#pragma once

#include "vulkan/vulkan.h"


namespace vkp {

  class VkpDescriptor 
  {
    public:
      VkpDescriptor();

    private:
      void CreateDescriptorSetLayout();
      void CreateDescriptorSets();
      void UpdateDescriptorSets();
      void Cleanup();


      VkDescriptorSetLayoutBinding layoutBinding;
      VkDescriptorSetLayout descriptorSetLayout;
      
  };

}



