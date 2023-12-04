project "Yumi"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    pchheader "YumiPCH.h"
    pchsource "Source/YumiPCH.cpp"
    forceincludes { "YumiPCH.h" }

    targetdir (targetroot .. "%{prj.name}")
    objdir (objroot .. "%{prj.name}")

    files
    {
        "Source/**.h",
        "Source/**.cpp"
    }

    includedirs
    {
        "Source",
        "%{IncludeDirs.GLFW}",
        "%{IncludeDirs.GLAD}",
        "%{IncludeDirs.STB}",
        "%{IncludeDirs.entt}",
        "%{IncludeDirs.RTTR}",
        "%{IncludeDirs.rapidjson}"
    }

    links
    {
        "GLFW",
        "opengl32.lib",
        "GLAD",
        "RTTR"
    }

    filter "system:windows"
        systemversion "latest"

    -- ********************** DEBUG **********************
    
    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    defines
    {
        "YUMI_DEBUG"
    }

    -- ********************** RELEASE **********************

    filter "configurations:Release"
        runtime "Release"
        optimize "on"

    defines
    {
        "YUMI_RELEASE"
    }