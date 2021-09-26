-- ~/Source/Demo/premake5.lua

project "Demo"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"

    files { "**.h", "**.cpp" }
    
    includedirs
    {
        "%{wks.location}/Source/Kreckanism/",
        "%{wks.location}/ThirdParty/Include/"
    }

    links { "Kreckanism" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        optimize "On"
