-- ~/Source/Demo/premake5.lua

project "Demo"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    targetdir "bin/%{cfg.buildcfg}"
    objdir "obj/%{cfg.buildcfg}"

    files { "**.h", "**.cpp" }

    includedirs
    {
        "%{wks.location}/Source/",
        "%{wks.location}/ThirdParty/glad/include",
        "%{wks.location}/ThirdParty/glfw/include",
        "%{wks.location}/ThirdParty/glm",
        "%{wks.location}/ThirdParty/imgui"
    }

    filter "system:linux"
        links { "Kreckanism", "glfw", "glad", "imgui", "GL", "rt", "m", "dl", "X11", "pthread" }

    filter "system:windows"
        includedirs { "D:/Program Files/Autodesk/FBX/FBX SDK/2020.2.1/include" }
        libdirs { "D:/Program Files/Autodesk/FBX/FBX SDK/2020.2.1/lib/vs2019/x64/debug" }
        links { "Kreckanism", "glfw", "glad", "imgui", "opengl32", "libfbxsdk-md", "libxml2-md", "zlib-md" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        optimize "On"
