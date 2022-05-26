-- ~/Source/Demo/premake5.lua

project "Sphectory"
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
        "%{wks.location}/ThirdParty/imgui",
        "%{wks.location}/ThirdParty/fmt/include"
    }

    filter "system:linux"
        includedirs
        {
            "/opt/fbxsdk/include",
            "/opt/fmod-studio-api/api/core/inc",
            "/opt/fmod-studio-api/api/studio/inc",
            "/opt/fmod-studio-api/api/fsbank/inc"
        }
        libdirs
        {
            "/opt/fbxsdk/lib/gcc/x64/debug",
            "/opt/fmod-studio-api/api/core/lib/x86_64",
            "/opt/fmod-studio-api/api/studio/lib/x86_64",
            "/opt/fmod-studio-api/api/fsbank/lib/x86_64"
        }
        links { "Kreckanism", "glfw", "glad", "imgui", "fmt", "GL", "rt", "m", "dl", "X11", "pthread", "fbxsdk", "xml2", "fmod", "fmodstudio" }

    filter "system:windows"
        includedirs
        {
            "D:/Program Files/Autodesk/FBX/FBX SDK/2020.2.1/include",
            "D:/Program Files (x86)/FMOD SoundSystem/FMOD Studio API Windows/api/core/inc",
            "D:/Program Files (x86)/FMOD SoundSystem/FMOD Studio API Windows/api/studio/inc",
            "D:/Program Files (x86)/FMOD SoundSystem/FMOD Studio API Windows/api/fsbank/inc"
        }
        libdirs
        {
             "D:/Program Files/Autodesk/FBX/FBX SDK/2020.2.1/lib/vs2019/x64/debug",
             "D:/Program Files (x86)/FMOD SoundSystem/FMOD Studio API Windows/api/core/lib/x64",
             "D:/Program Files (x86)/FMOD SoundSystem/FMOD Studio API Windows/api/studio/lib/x64",
             "D:/Program Files (x86)/FMOD SoundSystem/FMOD Studio API Windows/api/fsbank/lib/x64"
        }
        links { "Kreckanism", "glfw", "glad", "imgui", "fmt", "opengl32", "libfbxsdk-md", "libxml2-md", "zlib-md", "fmodL_vc", "fmodstudioL_vc", "fsbank_vc" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        optimize "On"
