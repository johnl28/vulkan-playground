#pragma once

#include <set>
#include <array>
#include <vector>
#include <optional>
#include <filesystem>

#include <glm/glm.hpp>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>





namespace vkp 
{

  typedef std::filesystem::path VkpFilePath;

  struct QueueFamilyIndices 
  {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool IsComplete()
    {
      return graphicsFamily.has_value() && presentFamily.has_value();
    }

    std::set<uint32_t> ToSet() 
    {
      return {  
        graphicsFamily.value(), 
        presentFamily.value()
      };
    }
  };

  struct SwapChainSupportDetails 
  {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
  };

  struct Vertex 
  {
    glm::vec2 pos;
    glm::vec3 color;

    static VkVertexInputBindingDescription getBindingDescription() 
    {
      VkVertexInputBindingDescription bindingDescription{};
      bindingDescription.binding = 0;
      bindingDescription.stride = sizeof(Vertex);
      bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

      return bindingDescription;
    }

    static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() 
    {
      std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};
      attributeDescriptions[0].binding = 0;
      attributeDescriptions[0].location = 0;
      attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
      attributeDescriptions[0].offset = offsetof(Vertex, pos);

      attributeDescriptions[1].binding = 0;
      attributeDescriptions[1].location = 1;
      attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
      attributeDescriptions[1].offset = offsetof(Vertex, color);
  
      return attributeDescriptions;
    }
  };

  struct UniformBufferObject 
  {
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
  };

} 