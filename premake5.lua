workspace "Shunya"
    architecture "x64"
    startproject "Shunya-Editor" -- Start with the Editor
    configurations { "Debug", "Release", "Dist" }
    
    filter "system:windows"
        buildoptions { "/utf-8" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Shunya-Core/third_party/GLFW/include"
IncludeDir["Glad"] = "Shunya-Core/third_party/Glad/include"
IncludeDir["imGUI"] = "Shunya-Core/third_party/imGUI"
IncludeDir["glm"] = "Shunya-Core/third_party/glm"
IncludeDir["stb_image"] = "Shunya-Core/third_party/stb_image"
IncludeDir["entt"] = "Shunya-Core/third_party/entt/include"

group "Dependencies"
    include "Shunya-Core/third_party/GLFW"
    include "Shunya-Core/third_party/Glad"
    include "Shunya-Core/third_party/imGUI"
group ""

project "Shunya-Core"
    location "Shunya-Core"
    kind "StaticLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "off" -- Switch to Dynamic to match /MDd

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
        "%{prj.name}/third_party/imGUI/examples/imgui_impl_opengl3.h"
    }

    includedirs {
        "%{prj.name}/src",
        "%{prj.name}/third_party/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.imGUI}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}",
        "%{IncludeDir.entt}"
    }

    links { "GLFW", "Glad", "imGUI", "opengl32.lib" }

    filter "system:windows"
        systemversion "latest"
        defines { "SHUNYA_CORE_EXPORTS", "IMGUI_DISABLE_WIN32_FUNCTIONS", "GLFW_INCLUDE_NONE" }

    filter "configurations:Debug"
        defines { "SHUNYA_DEBUG" }
        runtime "Debug" -- This replaces manual /MDd
        symbols "On"

    filter "configurations:Release"
        defines { "SHUNYA_RELEASE" }
        runtime "Release" -- This replaces manual /MD
        optimize "On"

    filter "configurations:Dist"
        defines { "SHUNYA_DIST" }
        runtime "Release"
        optimize "On"

-- Client Template Function
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
            "%{IncludeDir.entt}"
        }
        links { "Shunya-Core" }

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