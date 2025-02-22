#include "VKPlayground.h"

#include <iostream>
#include <stdexcept>
#include <cstdlib>

int main() {

  vkp::VKApp vulkanApp;

  try 
  {
    vulkanApp.Run();
  } 
  catch (const std::exception &e)
  {
    std::cout << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  
  vulkanApp.Cleanup();

  std::cout << "Application terminated successfully." << std::endl;
  return EXIT_SUCCESS;
}