#ifndef MODEL_H
#define MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>
#include <string>
#include <iostream>

#include "graphics/mesh.hpp"

class Model
{
    public:
        Model(const std::string& path);
        virtual ~Model();

        void draw(Shader& shader);
    
    private:
        // Model Data
        std::vector<Mesh> meshes;
        std::vector<Texture> texturesLoaded;
        std::string directory;

        void loadModel(const std::string& path);
        void processNode(aiNode* node, const aiScene* scene);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial* material, aiTextureType type, const std::string& typeName);
};

#endif // MODEL_H
