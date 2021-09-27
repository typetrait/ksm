-- ~/ThirdParty/glad.lua

project "glad"
    kind "StaticLib"
    language "C"

    location "glad/"
    targetdir "glad/bin/%{cfg.buildcfg}"
    objdir "glad/obj/%{cfg.buildcfg}"

    files
    {
        "glad/include/glad/glad.h",
        "glad/include/KHR/khrplatform.h",
        "glad/src/glad.c"
    }

    includedirs
    {
        "glad/include"
    }

    filter "configurations:Debug"
        symbols "on"

    filter "configurations:Release"
        optimize "on"
