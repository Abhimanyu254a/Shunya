workspace "Shunya"

    architecture "x64"
    configurations {"Debug","Release","dist"}
    filter "system:windows"
        buildoptions { "/utf-8" }
    

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Shunya-Core"
    location "Shunya-Core"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir.. "/%{prj.name}")
    objdir ("bin/" .. outputdir.. "/%{prj.name}")

    files{
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }
    includedirs{
        "%{prj.name}/third_party/spdlog/include"
    }

    filter "system:windows"
        cppdialect "C++latest"
        staticruntime "On"
        systemversion "latest"

        defines{
            "SHUNYA_CORE_EXPORTS", 
            "SHUNYA_BUILD_DLL"
        }

        postbuildcommands{
            ("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir.. "/PlayGround")
            --("copy /B /Y ..\\bin\\" .. outputdir .. "\\Shunya-Core\\Shunya-Core.dll ..\\bin\\" .. outputdir .. "\\PlayGround\\ > nul")
            --("{COPYDIR} \"%{wks.location}/bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/Shunya-Core/Shunya-Core.dll\" \"%{cfg.targetdir}\"")
        }
    
    filter "configurations:Debug" 
        defines {"Shunya_DEBUG"}
        symbols "On"
    
    filter "configurations:Release" 
        defines {"Shunya_RELEASE"}
        optimize "On"
    
    filter "configurations:Dist" 
        defines {"Shunya_DIST"}
        optimize "On"

project "PlayGround"
    location "PlayGround"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir.. "/%{prj.name}")
    objdir ("bin/" .. outputdir.. "/%{prj.name}")

    files{
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
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

        postbuildcommands{
        -- Use {COPY} for single files, which generates the 'copy' command
            ("{COPY} \"%{wks.location}/bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/Shunya-Core/Shunya-Core.dll\" \"%{cfg.targetdir}\"")
        }

        -- Old code bro --
        -- postbuildcommands{
        --     ("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir.. "/PlayGround")
        -- }
    
    filter "configurations:Debug" 
        defines {"Shunya_DEBUG"}
        symbols "On"
    
    filter "configurations:Release" 
        defines {"Shunya_RELEASE"}
        optimize "On"
    
    filter "configurations:Dist" 
        defines {"Shunya_DIST"}
        optimize "On"