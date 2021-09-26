-- ~/ThirdParty/premake5.lua

function build_thirdparty ()
  if os.get() == "windows" then
    build_glfw_windows()
  elseif os.get() == "linux" then
    build_glfw_unix()
  end
end

function build_glfw_windows ()
  os.execute "mkdir ThirdParty/Include ThirdParty/Lib"
  os.execute "cmake -SThirdParty/glfw -BThirdParty/glfw/build/ -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF"
  os.execute "make -CThirdParty/glfw/build/"
  os.execute "cp ThirdParty/glfw/build/src/glfw3.lib ThirdParty/Lib/"
  os.execute "cp -r ThirdParty/glfw/include/GLFW/ ThirdParty/Include/"
end

function build_glfw_unix ()
  os.execute "mkdir ThirdParty/Include ThirdParty/Lib"
  os.execute "cmake -SThirdParty/glfw -BThirdParty/glfw/build/ -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF"
  os.execute "make -CThirdParty/glfw/build/"
  os.execute "cp ThirdParty/glfw/build/src/libglfw3.a ThirdParty/Lib/"
  os.execute "cp -r ThirdParty/glfw/include/GLFW/ ThirdParty/Include/"
end