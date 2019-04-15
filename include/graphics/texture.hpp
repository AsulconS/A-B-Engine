#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

#include <string>
#include <iostream>

class Texture
{
    public:
        Texture();
        Texture(const char* _filename, const std::string& directory, const std::string& _type);
        virtual ~Texture();

        void load(const char* _filename, const std::string& directory, const std::string& _type);
        void free();
        void bind();

        std::string getFilename();
        std::string getType();

    private:
        // Texture by itself
        GLuint texture;

        std::string filename;
        std::string type;
};

#endif // TEXTURE_H
