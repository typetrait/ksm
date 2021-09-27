-- ~/ThirdParty/premake5.lua

function build_thirdparty ()
    os.execute "mkdir ThirdParty/Include ThirdParty/Lib"
    if os.host() == "windows" then
        build_glfw_windows()
        build_glad_windows()
    elseif os.host() == "linux" then
        build_glfw_linux()
        build_glad_linux()
    end
end

function build_glfw_windows ()
    os.execute "cmake -SThirdParty/glfw -BThirdParty/glfw/build/ -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF"
    os.execute "make -CThirdParty/glfw/build/"
    os.execute "cp ThirdParty/glfw/build/src/glfw3.lib ThirdParty/Lib/"
    os.execute "cp -r ThirdParty/glfw/include/GLFW/ ThirdParty/Include/"
end

function build_glfw_linux ()
    os.execute "cmake -SThirdParty/glfw -BThirdParty/glfw/build/ -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF"
    os.execute "make -CThirdParty/glfw/build/"
    os.execute "cp ThirdParty/glfw/build/src/libglfw3.a ThirdParty/Lib/"
    os.execute "cp -r ThirdParty/glfw/include/GLFW/ ThirdParty/Include/"
end

function build_glad_windows ()

end

function build_glad_linux ()
    os.execute "gcc -o ThirdParty/glad/src/glad.o -c ThirdParty/glad/src/glad.c -IThirdParty/glad/include/"
	  os.execute "ar rs ThirdParty/Lib/libglad.a ThirdParty/glad/src/glad.o"
    os.execute "cp -r ThirdParty/glad/include/* ThirdParty/Include/"
end
