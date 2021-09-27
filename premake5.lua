-- ~/premake5.lua

workspace "Kreckanism"
    configurations { "Debug", "Release" }
    startproject "Demo"

include "ThirdParty/glad.lua"
include "ThirdParty/glfw.lua"

include "Source/Kreckanism"
include "Source/Demo"
