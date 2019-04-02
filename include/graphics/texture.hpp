#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

#include <string>
#include <iostream>

class Texture
{
    public:
        Texture(const std::string& name, GLenum format, int texUnit);
        virtual ~Texture();

        void bind();

    private:
        // Texture by itself
        GLuint texture;
        int textureUnit;

        // RAW Data
        int width;
        int height;
        int nrChannels;
        unsigned char* data;
};

class Texture2
{
    public:
        Texture2(const std::string& name1, GLenum format1, int texUnit1, const std::string& name2, GLenum format2, int texUnit2);
        virtual ~Texture2();

        void bind();

    private:
        // Texture by itself
        GLuint texture[2];
        int textureUnit[2];

        // RAW Data
        int width[2];
        int height[2];
        int nrChannels[2];
        unsigned char* data[2];
};

#endif // TEXTURE_H
