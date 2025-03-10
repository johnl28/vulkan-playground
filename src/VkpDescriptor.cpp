
#include "VkpDescriptor.h"
#include "constants.h"

vkp::VkpDescriptor::VkpDescriptor()
{
  CreateDescriptorSetLayout();
  CreateDescriptorSets();
  UpdateDescriptorSets();
}

void vkp::VkpDescriptor::CreateDescriptorSetLayout()
{
  VkDescriptorSetLayoutBinding uboLayoutBinding{};
  uboLayoutBinding.binding = 0;
  uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  uboLayoutBinding.descriptorCount = 1;
  uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
  uboLayoutBinding.pImmutableSamplers = nullptr; 
}

void vkp::VkpDescriptor::CreateDescriptorSets()
{
}

void vkp::VkpDescriptor::UpdateDescriptorSets()
{
}

void vkp::VkpDescriptor::Cleanup()
{
}
