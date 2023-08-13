
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
targetroot = "%{wks.location}/Binaries/" .. outputdir .. "/"
objroot = "%{wks.location}/Intermediate/" .. outputdir .. "/"

IncludeDirs = {}

IncludeDirs["Yumi"] = "%{wks.location}/Engine/Yumi/Source"