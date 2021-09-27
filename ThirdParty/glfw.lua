-- ~/ThirdParty/glfw.lua

externalproject "glfw3"
    kind "StaticLib"
    language "C++"
    uuid "72f4a020-1f4d-11ec-8367-0800200c9a66"

    location "glfw/build/src/"
    targetdir "glfw/build/src/"

    os.execute "cmake -Sglfw/. -Bglfw/build/ -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF"
    if os.host == "windows" then
        print "glfw windows build"
    elseif os.host == "linux" then
        os.execute "make -Cglfw/build/"
    end
