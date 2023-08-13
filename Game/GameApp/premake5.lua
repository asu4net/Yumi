project "GameApp"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

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
        "%{IncludeDirs.Yumi}"
    }

    links
    {
        "Yumi"
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