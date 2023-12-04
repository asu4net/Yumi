workspace "Yumi"
    architecture "x86_64"
    startproject "GameApp"

    configurations
    {
        "Debug",
        "Release"
    }

include "Directories.lua"

group "Engine"
    include "Engine/Yumi/premake5.lua"
group ""

group "ThirdParty"
    include "ThirdParty/GLFW/premake5.lua"
    include "ThirdParty/GLAD/premake5.lua"
    include "ThirdParty/RTTR/premake5.lua"
group ""

group "Game"
    include "Game/GameApp/premake5.lua"
group ""