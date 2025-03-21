#include "gui.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_vulkan.h"

void vkp::GUI::Init(GuiInitInfo initInfo)
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style

    ImGuiStyle* dst = &ImGui::GetStyle();
    ImGui::StyleColorsDark(dst);
    dst->Colors[ImGuiCol_TitleBg]                = ImVec4(1.0f, 0.1f, 0.04f, 1.00f);
    dst->Colors[ImGuiCol_TitleBgActive]          = ImVec4(1.0f, 0.0f, 0.0f, 1.00f);
    dst->Colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(1.0f, 0.00f, 0.00f, 0.51f);
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForVulkan(initInfo.window, true);
    ImGui_ImplVulkan_InitInfo init_info = {};
    //init_info.ApiVersion = VK_API_VERSION_1_3;              // Pass in your value of VkApplicationInfo::apiVersion, otherwise will default to header version.
    init_info.Instance = initInfo.instance;
    init_info.PhysicalDevice = initInfo.physicalDevice;
    init_info.Device = initInfo.device;
    init_info.QueueFamily = initInfo.queueFamily;
    init_info.Queue = initInfo.queue;
    init_info.PipelineCache = initInfo.pipelineCache;
    init_info.DescriptorPool = initInfo.descriptorPool;
    init_info.RenderPass = initInfo.renderPass;
    init_info.Subpass = 0;
    init_info.MinImageCount = initInfo.minImageCount;
    init_info.ImageCount = initInfo.imageCount;
    init_info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
    init_info.Allocator = initInfo.allocator;
    init_info.CheckVkResultFn = nullptr;
    ImGui_ImplVulkan_Init(&init_info);
}

void vkp::GUI::Render(VkCommandBuffer commandBuffer)
{
  ImGui_ImplVulkan_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  RenderGeneralInfo();

  ImGui::Render();
  auto raw_data = ImGui::GetDrawData();
  ImGui_ImplVulkan_RenderDrawData(raw_data, commandBuffer);

}

void vkp::GUI::Cleanup()
{
  ImGui_ImplVulkan_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void vkp::GUI::RenderGeneralInfo()
{
  ImGuiIO& io = ImGui::GetIO(); 

  ImGui::Begin("General Info");

  ImGui::Text("Device: %s", generalInfo.DeviceName.c_str());
  ImGui::Text("Device Type: %s", generalInfo.DeviceType.c_str());
  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

  ImGui::End();
}
