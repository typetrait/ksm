#pragma once

#include <string>

namespace Ksm
{
    class Texture
    {
    public:
        Texture(const std::string& path, bool flip=true);
        ~Texture();
        void Bind();
        void Unbind();

    private:
        unsigned int id;
        unsigned int width;
        unsigned int height;
        std::string path;
    };
}
