#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "graphics/shader.hpp"
#include "graphics/texture.hpp"

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 UV;
};

class Mesh
{
public:
    Mesh(const std::vector<Vertex>& v, const std::vector<GLuint>& i, const std::vector<Texture>& t);
    virtual ~Mesh();

    void draw(Shader& shader);
    void freeMesh();

    static void loadDefaultSpecTex();

private:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;

    GLuint VAO, VBO, EBO;

    static Texture defaultSpecTex;

    void setupMesh();
};

#endif // MESH_H
