#include "VkpApp.h"

#include <iostream>
#include <stdexcept>
#include <cstdlib>

int main() {

  vkp::VkpApp vulkanApp;

  try 
  {
    vulkanApp.Run();

    vulkanApp.Cleanup();
    std::cout << "Application terminated successfully." << std::endl;
  } 
  catch (const std::exception &e)
  {
    std::cout << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  

  return EXIT_SUCCESS;
}