# Vulkan Playground

A **playground** for the Vulkan API. 

This repository is used for **learning** and **experimenting** purposes, which means that it **won't** be optimised 
for the best compatibility or performance.


# Resources

- [Khronos Vulkan Tutorial](https://docs.vulkan.org/tutorial/latest/00_Introduction.html)
- [Vulkan YouTube Tutorials](https://www.youtube.com/playlist?list=PL8327DO66nu9qYVKLDmdLW_84-yE4auCR)
- [Vulkan Docs](https://docs.vulkan.org/spec/latest/chapters/fundamentals.html)
- [Devdocs](https://devdocs.io/vulkan/)
- [Renderdoc](https://renderdoc.org/)


# Platforms Tested

| OS                 | GPU                                              |
|--------------------|--------------------------------------------------|
| Ubuntu 24.04.2 LTS | Radeon RX Vega 6 (Ryzen 4000/5000 Mobile Series) |


# Dependencies

- [GLFW](https://www.glfw.org/)
- [LunarG Vulkan SDK](https://www.lunarg.com/vulkan-sdk/)
- [GLM](https://github.com/g-truc/glm)
- [ImGUI](https://github.com/ocornut/imgui)


# Build

```bash
sh build.sh && make test
```
