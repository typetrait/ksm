-- ~/premake5.lua

include "ThirdParty/premake5.lua"

build_thirdparty()

workspace "Kreckanism"
    configurations { "Debug", "Release" }
    startproject "Demo"

include "Source/Kreckanism"
include "Source/Demo"