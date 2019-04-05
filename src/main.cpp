#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#include "graphics.hpp"

// Settings
const unsigned int SCR_WIDTH = 1408; // 800 (LEGACY)
const unsigned int SCR_HEIGHT = 792; // 600 (LEGACY)
const float ASPECT = (float)SCR_WIDTH / (float)SCR_HEIGHT;

int main()
{
    Display display(SCR_WIDTH, SCR_HEIGHT, "OpenGL Test Window", 3);
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

    display.setCamera(&camera);

    // Shader lightingShader("directionalLight");
    // Shader lightingShader("pointLights");
    Shader lightingShader("lightingShader");
    Shader lampShader("lamp");

    float vertexData[] =
    {
        // Position           // Normal             // UV
        -0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,  0.0f, 0.0f,  // 0
         0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,  1.0f, 0.0f,  // 1
        -0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,  0.0f, 1.0f,  // 2
        -0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,  0.0f, 1.0f,  // 2
         0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,  1.0f, 0.0f,  // 1
         0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,  1.0f, 1.0f,  // 3

         0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f,  0.0f, 0.0f,  // 1
         0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,  1.0f, 0.0f,  // 5
         0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,  0.0f, 1.0f,  // 3
         0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,  0.0f, 1.0f,  // 3
         0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,  1.0f, 0.0f,  // 5
         0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f,  1.0f, 1.0f,  // 7

        -0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,  0.0f, 0.0f,  // 2
         0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,  1.0f, 0.0f,  // 3
        -0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,  0.0f, 1.0f,  // 6
        -0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,  0.0f, 1.0f,  // 6
         0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,  1.0f, 0.0f,  // 3
         0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,  1.0f, 1.0f,  // 7

         0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,  0.0f, 0.0f,  // 5
        -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,  1.0f, 0.0f,  // 4
         0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,  0.0f, 1.0f,  // 7
         0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,  0.0f, 1.0f,  // 7
        -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,  1.0f, 0.0f,  // 4
        -0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,  1.0f, 1.0f,  // 6

        -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,  // 4
        -0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,  // 0
        -0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,  // 6
        -0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,  // 6
        -0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,  // 0
        -0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,  // 2

        -0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,  0.0f, 0.0f,  // 4
         0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,  1.0f, 0.0f,  // 5
        -0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,  0.0f, 1.0f,  // 0
        -0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,  0.0f, 1.0f,  // 0
         0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,  1.0f, 0.0f,  // 5
         0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,  1.0f, 1.0f   // 1
    };
    glm::vec3 cubePositions[] =
    {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    glm::vec3 pointLightsPositions[] =
    {
        glm::vec3( 0.7f,  0.2f,  2.0f),
        glm::vec3( 2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  0.0f, -3.0f)
    };

    // CUBE
    // ----

    GLuint cubeVAO, cubeVBO;

    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, false, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);

    // LIGHT
    // -----
    GLuint lightVAO;

    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    Texture texture("container2.png", GL_RGBA, 0);
    Texture textureSpec("container2_specular.png", GL_RGBA, 1);

    lightingShader.use();

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view  = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    // Setting up Vertex Shader Uniforms
    lightingShader.setMat4("model", model);
    lightingShader.setMat4("view", view);
    lightingShader.setMat4("projection", projection);

    // Setting up Fragment Shader Uniforms
    lightingShader.setVec3("viewPos", camera.position);

    // Material Parameters
    lightingShader.setInt("material.diffuse", 0);
    lightingShader.setInt("material.specular", 1);
    lightingShader.setFloat("material.shininess", 64.0f);

    // Light Parameters
    // Directional Light
    lightingShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);

    // Light Intensity
    lightingShader.setVec3("dirLight.ambient", 0.2f, 0.2f, 0.2f);
    lightingShader.setVec3("dirLight.diffuse", 0.5f, 0.5f, 0.5f);
    lightingShader.setVec3("dirLight.specular", 1.0f, 1.0f, 1.0f);

    // Point Lights
    for (size_t i = 0; i < 4; i++)
    {
        std::string number = std::to_string(i);
     
        lightingShader.setVec3( "pointLights[" + number + "].position", pointLightsPositions[i]);

        lightingShader.setVec3( "pointLights[" + number + "].ambient", 0.2f, 0.2f, 0.2f);
        lightingShader.setVec3( "pointLights[" + number + "].diffuse", 0.5f, 0.5f, 0.5f);
        lightingShader.setVec3( "pointLights[" + number + "].specular", 1.0f, 1.0f, 1.0f);

        lightingShader.setFloat("pointLights[" + number + "].constant", 1.0f);
        lightingShader.setFloat("pointLights[" + number + "].linear", 0.09f);
        lightingShader.setFloat("pointLights[" + number + "].quadratic", 0.032f);
    }

    lightingShader.setVec3("spotLight.position", camera.position);
    lightingShader.setVec3("spotLight.direction", camera.getFront());

    lightingShader.setVec3("spotLight.ambient", 0.2f, 0.2f, 0.2f);
    lightingShader.setVec3("spotLight.diffuse", 0.5f, 0.5f, 0.5f);
    lightingShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);

    lightingShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
    lightingShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(17.5f)));

    lightingShader.setFloat("sporLight.constant", 1.0f);
    lightingShader.setFloat("spotLight.linear", 0.09f);
    lightingShader.setFloat("spotLight.quadratic", 0.032f);

    // glPolygonMode(GL_FRONT, GL_LINE);
    while(display.active())
    {
        // Processing Input
        display.processInput();

        // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Rendering Process
        // -----------------
        // Camera Processing
        view = camera.getViewMatrix();
        projection = camera.getProjectionMatrix(ASPECT);

        lightingShader.use();
        lightingShader.setMat4("view", view);
        lightingShader.setMat4("projection", projection);

        lightingShader.setVec3("viewPos", camera.position);
        lightingShader.setVec3("spotLight.position", camera.position);
        lightingShader.setVec3("spotLight.direction", camera.getFront());

        // Texture Processing
        texture.bind();
        textureSpec.bind();

        // Model Processing
        glBindVertexArray(cubeVAO);
        for(size_t i = 0; i < 10; ++i)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            lightingShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        glBindVertexArray(0);

        // ------------------

        glBindVertexArray(lightVAO);
        for(size_t i = 0; i < 4; ++i)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightsPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f));

            lampShader.use();
            lampShader.setMat4("model", model);
            lampShader.setMat4("view", view);
            lampShader.setMat4("projection", projection);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        glBindVertexArray(0);

        display.swapBuffers();
        display.pollEvents();
    }

    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteBuffers(1, &cubeVBO);

    glfwTerminate();
    return 0;
}
