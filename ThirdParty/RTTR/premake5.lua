project "RTTR"
    kind "StaticLib"
    language "C++"
    staticruntime "off"
    
    targetdir (targetroot .. "%{prj.name}")
    objdir (objroot .. "%{prj.name}")

    files
    {
        "src/rttr/**.h",
        "src/rttr/**.h.in",
        "src/rttr/**.cpp"
    }

    includedirs
    {
        "%{IncludeDirs.RTTR}"
    }

    defines 
    {
    }

    filter "system:windows"
        systemversion "latest"
        staticruntime "off"

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