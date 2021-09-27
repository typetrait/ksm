-- ~/Source/Demo/premake5.lua

project "Demo"
    kind "ConsoleApp"
    language "C++"

    targetdir "bin/%{cfg.buildcfg}"
    objdir "obj/%{cfg.buildcfg}"

    files { "**.h", "**.cpp" }
    
    includedirs
    {
        "%{wks.location}/Source/",
        "%{wks.location}/ThirdParty/glad/include",
        "%{wks.location}/ThirdParty/glfw/include"
    }

    libdirs
    {
        "%{wks.location}/ThirdParty/Lib/"
    }

    filter "system:linux"

        links { "Kreckanism", "glfw3", "glad", "GL", "rt", "m", "dl", "X11", "pthread" }

    filter "system:windows"

        links { "Kreckanism", "glfw3", "glad", "opengl32" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        optimize "On"
