-- ~/premake5.lua

workspace "Kreckanism"
    configurations { "Debug", "Release" }
    startproject "Demo"
    architecture "x86_64"

include "ThirdParty/glad.lua"
include "ThirdParty/glfw.lua"
include "ThirdParty/imgui.lua"
include "ThirdParty/fmt.lua"

include "Source/Kreckanism"
include "Source/Demo"
