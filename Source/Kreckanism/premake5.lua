-- ~/Source/Kreckanism/premake5.lua

project "Kreckanism"
    kind "StaticLib"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"

	files { "**.h", "**.cpp" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        optimize "On"
