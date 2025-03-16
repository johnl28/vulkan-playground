#pragma once

#include <vector>
#include <fstream>

#include "VkpCore.h"

namespace vkp {
  class Utils
  {
    public:
      static std::vector<char> ReadShaderFile(const VkpFilePath& filename) 
      {
        std::ifstream file(filename, std::ios::ate | std::ios::binary);
    
        if (!file.is_open()) 
        {
          throw std::runtime_error("Failed to open file: {}");
        }

        size_t fileSize = (size_t) file.tellg();
        std::vector<char> buffer(fileSize);


        file.seekg(0);
        file.read(buffer.data(), fileSize);

        file.close();

        return buffer;
      }
  };
}