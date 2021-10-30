#pragma once

#include <string>

namespace Ksm
{
    class Texture
    {
    public:
        Texture(const std::string& path);
        ~Texture();
        void Bind();
        void Unbind();

    private:
        unsigned int id;
        unsigned int width;
        unsigned int height;
        const std::string& path;
    };
}
