-- ~/ThirdParty/fmt.lua

externalproject "fmt"
    kind "StaticLib"
    language "C++"
    uuid "c7988f50-4668-11ec-8072-0800200c9a66"

    location "fmt/build"
    targetdir "fmt/build"
    targetname "fmt"

    os.execute "cmake -Sfmt/ -Bfmt/build/ -DFMT_TEST=FALSE"
    os.execute "cmake --build fmt/build/"
