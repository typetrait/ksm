-- ~/ThirdParty/glfw.lua

externalproject "glfw"
    kind "StaticLib"
    language "C++"
    uuid "72f4a020-1f4d-11ec-8367-0800200c9a66"

    location "glfw/build/src/"
    targetdir ("glfw/build/src/" .. ((os.host == "windows") and "Debug/" or ""))
    targetname "glfw3"

    os.execute "cmake -Sglfw/ -Bglfw/build/ -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF"
    os.execute "cmake --build glfw/build/"
