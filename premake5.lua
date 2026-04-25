workspace "Shunya"
    architecture "x64"
    startproject "Shunya-Editor" 
    configurations { "Debug", "Release", "Dist" }
    
    filter "system:windows"
        buildoptions { "/utf-8" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- ==============================================================================
-- 1. DEFINE ALL VARIABLES FIRST (Before any projects are declared)
-- ==============================================================================

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

-- ==============================================================================
-- 2. NOW DECLARE THE PROJECTS
-- ==============================================================================

group "Dependencies"
    include "Shunya-Core/third_party/GLFW"
    include "Shunya-Core/third_party/Glad"
    include "Shunya-Core/third_party/imGUI"
    include "Shunya-Core/third_party/yaml_cpp"
    include "Shunya-Core/third_party/ImGizmos"
group ""

project "Shunya-Core"
    location "Shunya-Core"
    kind "StaticLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "off" 

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin/" .. outputdir .. "/%{prj.name}")

    pchheader "SNY-PCH.h"
    pchsource "Shunya-Core/src/SNY-PCH.cpp"

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/third_party/glm/**.hpp",
        "%{prj.name}/third_party/glm/**.inl",
        "%{prj.name}/third_party/stb_image/**.cpp",
        "%{prj.name}/third_party/stb_image/**.h",
        "%{prj.name}/third_party/imGUI/examples/imgui_impl_glfw.h",
        "%{prj.name}/third_party/imGUI/examples/imgui_impl_glfw.cpp",
        "%{prj.name}/third_party/imGUI/examples/imgui_impl_opengl3.cpp",
        "%{prj.name}/third_party/imGUI/examples/imgui_impl_opengl3.h",
    }

    includedirs {
        "%{prj.name}/src",
        "%{prj.name}/third_party/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.imGUI}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}",
        "%{IncludeDir.entt}",
        "%{IncludeDir.yaml_cpp}",
        "%{IncludeDir.ImGizmos}",
        "%{IncludeDir.VulkanSDK}"
    }

    links { "GLFW", "Glad", "imGUI","yaml_cpp","opengl32.lib","ImGizmos" }

    filter "files:third_party/ImGizmos/**.cpp"
        flags {"NoPCH"}

    filter "system:windows"
        systemversion "latest"
        defines { "SHUNYA_CORE_EXPORTS", "IMGUI_DISABLE_WIN32_FUNCTIONS", "GLFW_INCLUDE_NONE","YAML_CPP_STATIC_DEFINE" }

    filter "configurations:Debug"
        defines { "SHUNYA_DEBUG", "YAML_CPP_STATIC_DEFINE" }
        runtime "Debug" 
        symbols "On"
        links{
            "%{Library.ShaderC_Debug}",
            "%{Library.SPIRV_Cross_Debug}",
            "%{Library.SPIRV_Cross_GLSL_Debug}"
        }

    filter "configurations:Release"
        defines { "SHUNYA_RELEASE", "YAML_CPP_STATIC_DEFINE" }
        runtime "Release" 
        optimize "On"
        links{
            "%{Library.ShaderC_Release}",
            "%{Library.SPIRV_Cross_Release}",
            "%{Library.SPIRV_Cross_GLSL_Release}"
        }   

    filter "configurations:Dist"
        defines { "SHUNYA_DIST" }
        runtime "Release"
        optimize "On"
        links{
            "%{Library.ShaderC_Release}",
            "%{Library.SPIRV_Cross_Release}",
            "%{Library.SPIRV_Cross_GLSL_Release}"
        }

-- ==============================================================================
-- 3. CLIENT TEMPLATE
-- ==============================================================================

function CreateClientProject(name)
    project (name)
        location (name)
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++latest"
        staticruntime "off"

        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("bin/" .. outputdir .. "/%{prj.name}")

        files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }
        includedirs {
            "Shunya-Core/src",
            "Shunya-Core/third_party/spdlog/include",
            "%{IncludeDir.glm}",
            "%{IncludeDir.imGUI}",
            "%{IncludeDir.GLFW}",
            "%{IncludeDir.Glad}",
            "%{IncludeDir.stb_image}",
            "%{IncludeDir.entt}",
            "%{IncludeDir.yaml_cpp}",
            "%{IncludeDir.ImGizmos}"
        }
        links { "Shunya-Core" }

        filter "files:third_party/ImGizmos/**.cpp"
            flags {"NoPCH"}
        
        filter "system:windows"
            systemversion "latest"

        filter "configurations:Debug"
            defines { "SHUNYA_DEBUG" }
            runtime "Debug"
            symbols "On"

        filter "configurations:Release"
            defines { "SHUNYA_RELEASE" }
            runtime "Release"
            optimize "On"
end

CreateClientProject("PlayGround")
CreateClientProject("Shunya-Editor")