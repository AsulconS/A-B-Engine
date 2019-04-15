#include "graphics/mesh.hpp"

Texture Mesh::defaultSpecTex;

void Mesh::loadDefaultSpecTex()
{
    defaultSpecTex.load("default.png", "res/textures", "texture_specular");
}

Mesh::Mesh(const std::vector<Vertex>& v, const std::vector<GLuint>& i, const std::vector<Texture>& t)
    : vertices(v), indices(i), textures(t)
{
    setupMesh();
}

Mesh::~Mesh()
{
    //
}

void Mesh::draw(Shader& shader)
{
    shader.use();
    for(size_t i = 0; i < textures.size(); ++i)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        shader.setFloat("material." + textures[i].getType(), i);
        textures[i].bind();
    }
    if(textures.size() == 1)
    {
        glActiveTexture(GL_TEXTURE1);
        shader.setFloat("material.texture_specular", 1);
        defaultSpecTex.bind();
    }

    glActiveTexture(GL_TEXTURE0);

    // Draw Mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::setupMesh()
{
    // Create buffers/arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_DYNAMIC_DRAW);

    // Vertex Positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Vertex Normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);
    // Vertex UVs
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, UV));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void Mesh::freeMesh()
{
    for(size_t i = 0; i < textures.size(); ++i)
        textures[i].free();

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
