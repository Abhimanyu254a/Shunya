workspace "Shunya"

    architecture "x64"
    startproject "PlayGround"
    configurations {"Debug","Release","dist"}
    filter "system:windows"
        buildoptions { "/utf-8" }
    

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Shunya-Core/third_party/GLFW/include"
IncludeDir["Glad"] = "Shunya-Core/third_party/Glad/include"
IncludeDir["imGUI"] = "Shunya-Core/third_party/imGUI"
IncludeDir["glm"] = "Shunya-Core/third_party/glm"
IncludeDir["stb_image"] = "Shunya-Core/third_party/stb_image"

include "Shunya-Core\\third_party\\GLFW"
include "Shunya-Core\\third_party\\Glad"
include "Shunya-Core\\third_party\\imGUI"
include "Shunya-Core\\third_party\\glm"
include "Shunya-Core\\third_party\\stb_image"




project "Shunya-Core"
    location "Shunya-Core"
    kind "StaticLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "on"

    targetdir ("bin/" .. outputdir.. "/%{prj.name}")
    objdir ("bin/" .. outputdir.. "/%{prj.name}")

    pchheader "SNY-PCH.h"
    pchsource "Shunya-Core/src/SNY-PCH.cpp"

    files{
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
    includedirs{
        "%{prj.name}/src",
        "%{prj.name}/third_party/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.imGUI}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}"

    }

    links{
        "GLFW",
        "Glad",
        "imGUI",
        "opengl32.lib"
    }

    filter "system:windows"

        staticruntime "On"
        systemversion "latest"

        defines{
            "SHUNYA_CORE_EXPORTS", 
            "SHUNYA_BUILD_DLL",
            "IMGUI_DISABLE_WIN32_FUNCTIONS",
            "GLFW_INCLUDE_NONE"
        }

        -- postbuildcommands{
        --     ("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir.. "/PlayGround")
        --     --("copy /B /Y ..\\bin\\" .. outputdir .. "\\Shunya-Core\\Shunya-Core.dll ..\\bin\\" .. outputdir .. "\\PlayGround\\ > nul")
        --     --("{COPYDIR} \"%{wks.location}/bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/Shunya-Core/Shunya-Core.dll\" \"%{cfg.targetdir}\"")
        -- }
    
    filter "configurations:Debug" 
        defines {"Shunya_DEBUG"}
        buildoptions "/MDd"
        symbols "On"
    
    filter "configurations:Release" 
        defines {"Shunya_RELEASE"}
        buildoptions "/MD"
        optimize "On"
    
    filter "configurations:Dist" 
        defines {"Shunya_DIST"}
        buildoptions "/MD"
        optimize "On"

project "PlayGround"
    location "PlayGround"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir.. "/%{prj.name}")
    objdir ("bin/" .. outputdir.. "/%{prj.name}")

    files{
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{IncludeDir.glm}"
    }
    includedirs{
        "%{wks.location}/Shunya-Core/third_party/spdlog/include",
        "Shunya-Core/src"
    }
    
    links{
        "Shunya-Core"
    }

    filter "system:windows"
        cppdialect "C++latest"
        staticruntime "On"
        systemversion "latest"


        defines{
            "SHUNYA_CORE_EXPORTS" 
        }
        dependson { "Shunya-Core" } -- Ensure this dependency is set



        -- Old code bro --
        -- postbuildcommands{
        --     ("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir.. "/PlayGround")
        -- }
    
    filter "configurations:Debug" 
        defines {"Shunya_DEBUG"}
        buildoptions "/MDd"
        symbols "On"
    
    filter "configurations:Release" 
        defines {"Shunya_RELEASE"}
        buildoptions "/MD"
        optimize "On"
    
    filter "configurations:Dist" 
        defines {"Shunya_DIST"}
        buildoptions "/MD"
        optimize "On"