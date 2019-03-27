#include "graphics/texture.hpp"

#define  STB_IMAGE_IMPLEMENTATION
#include "graphics/stb_image.h"

Texture::Texture(const std::string& name, GLenum format)
{
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load RAW Data
    std::string path = "res/textures/" + name;
    stbi_set_flip_vertically_on_load(true);
    data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cerr << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

Texture2::Texture2(const std::string& name1, GLenum format1, const std::string& name2, GLenum format2)
{
    glGenTextures(2, texture);
    for(size_t i = 0; i < 2; ++i)
    {
        glBindTexture(GL_TEXTURE_2D, texture[i]);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Load RAW Data
        std::string path = "res/textures/" + ((i == 0) ? name1 : name2);
        stbi_set_flip_vertically_on_load(true);
        data[i] = stbi_load(path.c_str(), &width[i], &height[i], &nrChannels[i], 0);
        if(data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width[i], height[i], 0, ((i == 0) ? format1 : format2), GL_UNSIGNED_BYTE, data[i]);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cerr << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data[i]);
    }
}

Texture::~Texture()
{
    //
}

Texture2::~Texture2()
{
    //
}

void Texture::bind()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture2::bind()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
}
