
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
targetroot = "%{wks.location}/Binaries/" .. outputdir .. "/"
objroot = "%{wks.location}/Intermediate/" .. outputdir .. "/"

IncludeDirs = {}

IncludeDirs["Yumi"] = "%{wks.location}/Engine/Yumi/Source"
IncludeDirs["GLFW"] = "%{wks.location}/ThirdParty/GLFW/include"
IncludeDirs["GLAD"] = "%{wks.location}/ThirdParty/GLAD/include"
IncludeDirs["STB"] = "%{wks.location}/ThirdParty/STB/include"