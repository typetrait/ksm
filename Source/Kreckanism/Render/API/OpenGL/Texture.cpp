#include <Kreckanism/Render/API/OpenGL/Texture.h>

#include <string>

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Ksm
{
    Texture::Texture(const std::string& path) : path(path)
    {
        int width = 0;
        int height = 0;
        int channelCount = 0;
        unsigned char* data = nullptr;

        stbi_set_flip_vertically_on_load(true);
        data = stbi_load(path.c_str(), &width, &height, &channelCount, 0);

        if (data)
        {
            this->width = width;
            this->height = height;

            GLenum internalFormat = 0;
            GLenum format = 0;

            if (channelCount == 3)
            {
                internalFormat = GL_RGB8;
                format = GL_RGB;
            }
            else if (channelCount == 4)
            {
                internalFormat = GL_RGBA8;
                format = GL_RGBA;
            }

            glGenTextures(1, &id);
            glBindTexture(GL_TEXTURE_2D, id);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            stbi_image_free(data);
        }
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &id);
    }

    void Texture::Bind()
    {
        glBindTexture(GL_TEXTURE_2D, id);
    }

    void Texture::Unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
