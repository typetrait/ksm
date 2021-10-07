-- ~/ThirdParty/imgui.lua

project "imgui"
    kind "StaticLib"
    language "C++"

    location "imgui/build"
    targetdir "imgui/build/bin/%{cfg.buildcfg}"
    objdir "imgui/build/obj/%{cfg.buildcfg}"

    files
    {
        "imgui/imconfig.h",
        "imgui/imgui.cpp",
        "imgui/imgui.h",
        "imgui/imgui_demo.cpp",
        "imgui/imgui_draw.cpp",
        "imgui/imgui_internal.h",
        "imgui/imgui_tables.cpp",
        "imgui/imgui_widgets.cpp",
        "imgui/imstb_rectpack.h",
        "imgui/imstb_textedit.h",
        "imgui/imstb_truetype.h",
        "imgui/backends/imgui_impl_glfw.h",
        "imgui/backends/imgui_impl_glfw.cpp",
        "imgui/backends/imgui_impl_opengl3.h",
        "imgui/backends/imgui_impl_opengl3.cpp"
    }

    includedirs
    {
        "imgui/",
        "glfw/include"
    }

    filter "configurations:Debug"
        symbols "on"

    filter "configurations:Release"
        optimize "on"
