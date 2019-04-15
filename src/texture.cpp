#include "graphics/texture.hpp"

#define  STB_IMAGE_IMPLEMENTATION
#include "graphics/stb_image.h"

Texture::Texture()
{
    //
}

Texture::Texture(const char* _filename, const std::string& directory, const std::string& _type)
{
    load(_filename, directory, _type);
}

Texture::~Texture()
{
    //
}

void Texture::load(const char* _filename, const std::string& directory, const std::string& _type)
{
    filename = std::string(_filename);
    std::string path = directory + '/' + filename;
    type = _type;

    glGenTextures(1, &texture);
    int width, height, nrComponents; // stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
    // Load RAW Data
    if(data)
    {
        GLenum format;
        if(nrComponents == 1)
            format = GL_RED;
        else if(nrComponents == 3)
            format = GL_RGB;
        else if(nrComponents == 4)
            format = GL_RGBA;
        
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cerr << "Failed to load texture" << std::endl;
        stbi_image_free(data);
    }
}

void Texture::free()
{
    glDeleteTextures(1, &texture);
}

std::string Texture::getFilename()
{
    return filename;
}

std::string Texture::getType()
{
    return type;
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, texture);
}
