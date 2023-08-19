project "GLAD"
    kind "StaticLib"
    language "C"
    staticruntime "off"

    targetdir (targetroot .. "%{prj.name}")
    objdir (objroot .. "%{prj.name}")

    files
    {
        "include/glad/glad.h",
        "include/KHR/khrplatform.h",
        "src/glad.c"
    }

    includedirs
    {
        "include"
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