workspace "Lemon-Engine"

    architecture "x64"

    configurations 
    {
        "Debug",
        "Release",
        "Dist"
    }

    filter "system:windows"
        startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Lemon/vendor/glfw/include"
IncludeDir["Glad"] = "Lemon/vendor/glad/include"
IncludeDir["glm"] = "Lemon/vendor/glm"
IncludeDir["stb_image"] = "Lemon/vendor/stb/include"
IncludeDir["spdlog"] = "Lemon/vendor/spdlog/include"
IncludeDir["debugbreak"] = "Lemon/vendor/debug"

group "Dependencies"
    include "Lemon/vendor/glfw"
    include "Lemon/vendor/glad"
group ""

project "Lemon"
    location "Lemon"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "lmpch.h"
    pchsource "Lemon/src/lmpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/stb/include/**.h",
		"%{prj.name}/vendor/stb/include/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl",
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
		"%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.debugbreak}"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "LM_BUILD_DLL",
            "LM_PLATFORM_WINDOWS"
        }

        --postbuildcommands
        --{
        --    ("{COPY} ./Resources  ../bin/" .. outputdir .. "/%{prj.name}/")
        --}

        links
        {
            "GLFW",
            "Glad",
            "opengl32.lib"
        }

    filter "system:linux"
        systemversion "latest"

        defines
        {
            "LM_BUILD_DLL",
            "LM_PLATFORM_LINUX"
        }

        links
        {
            "GLFW",
            "Glad",
            "GL",
            "X11",
            "pthread",
            "Xrandr",
            "Xi",
            "dl"
        }
        
        --postbuildcommands
        --{
        --    ("{COPY} ./Resources  ../bin/" .. outputdir .. "/%{prj.name}/")
        --}

    filter "configurations:Debug"
        defines { "LM_DEBUG", "LM_ENABLE_ASSERTS" }
        symbols "On"
      
    filter "configurations:Release"
        defines "LM_RELEASE"
        optimize "On"
      
    filter "configurations:Dist"
        defines "LM_DIST"
        optimize "On"


project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "lmpch.h"
    pchsource "Lemon/src/lmpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}",
        "%{IncludeDir.spdlog}",
        "Lemon/src",
        "%{IncludeDir.debugbreak}"
    }

    links
    {
        "Lemon"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "LM_PLATFORM_WINDOWS"
        }

        --postbuildcommands
        --{
        --    ("{COPY} ./Resources  ../bin/" .. outputdir .. "/%{prj.name}/")
        --}

        links
        {
            "GLFW",
            "Glad",
            "opengl32.lib"
        }

    filter "system:linux"
        systemversion "latest"

        defines
        {
            "LM_PLATFORM_LINUX"
        }

        links
        {
            "GLFW",
            "Glad",
            "GL",
            "X11",
            "pthread",
            "Xrandr",
            "Xi",
            "dl"
        }
        
        --postbuildcommands
        --{
        --    ("{COPY} ./Resources  ../bin/" .. outputdir .. "/%{prj.name}/")
        --}

    filter "configurations:Debug"
        defines { "LM_DEBUG", "LM_ENABLE_ASSERTS" }
        symbols "On"
      
    filter "configurations:Release"
        defines "LM_RELEASE"
        optimize "On"
      
    filter "configurations:Dist"
        defines "LM_DIST"
        optimize "On"
