VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["GLFW"] = "Shunya-Core/third_party/GLFW/include"
IncludeDir["Glad"] = "Shunya-Core/third_party/Glad/include"
IncludeDir["imGUI"] = "Shunya-Core/third_party/imGUI"
IncludeDir["glm"] = "Shunya-Core/third_party/glm"
IncludeDir["stb_image"] = "Shunya-Core/third_party/stb_image"
IncludeDir["entt"] = "Shunya-Core/third_party/entt/include"
IncludeDir["yaml_cpp"] = "Shunya-Core/third_party/yaml_cpp/include"
IncludeDir["ImGizmos"] = "Shunya-Core/third_party/ImGizmos"
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"

LibraryDir = {}
LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"

Library = {}
Library["ShaderC_Debug"] = "%{LibraryDir.VulkanSDK}/shaderc_sharedd.lib"
Library["SPIRV_Cross_Debug"] = "%{LibraryDir.VulkanSDK}/spirv-cross-cored.lib"
Library["SPIRV_Cross_GLSL_Debug"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsld.lib"

Library["ShaderC_Release"] = "%{LibraryDir.VulkanSDK}/shaderc_shared.lib"
Library["SPIRV_Cross_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-core.lib"
Library["SPIRV_Cross_GLSL_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsl.lib"