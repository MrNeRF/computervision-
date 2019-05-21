#include <GL/glew.h>  
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>
#include <vector>
#include "Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "File.h"
#include "ObjFileParser.h"
#include "Camera.h"
// #define before glm includes activate c++14 language features
#define GLM_FORCE_CXX14
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


// camera
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

// lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

int main()
{
    // Initialise GLFW
    if( !glfwInit() )
    {
        std::cerr <<  "Failed to initialize GLFW\n"; 
        return -1;
    }
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

    // Open a window and create its OpenGL context
    GLFWwindow* window; // (In the accompanying source code, this variable is global for simplicity)
    window = glfwCreateWindow( 1024, 768, "Rendering with OpenGL", NULL, NULL);

    if( window == NULL )
    {
        std::cerr <<  "Failed to open GLFW window. \n" ;
        glfwTerminate();
        return -1;
    };
    glfwMakeContextCurrent(window); // Initialize GLEW
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) 
    {
        std::cerr <<  "Failed to initialize GLEW\n";
        return -1;
    }
    glEnable(GL_DEPTH_TEST);  

    // get version info
    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString(GL_VERSION); // version as a string
    std::cout << "Renderer: " <<  renderer << std::endl;
    std::cout << "OpenGL version supported \n" << version << std::endl;

    Shader lightingShader("../shader/color.vs", "../shader/color.fs");
    Shader lampShader("../shader/lamp.vs", "../shader/lamp.fs");
    std::vector<glm::vec3> vMonkey;
    std::vector<int> ivMonkey;

    ObjFileParser parseMonkey(std::make_unique<File>("../models/suzanne.obj"));
    parseMonkey.Parse();
    parseMonkey.GetVerticesOpenGL(vMonkey,ivMonkey);

    unsigned int monkeyVBO, monkeyVAO;
    glGenVertexArrays(1, &monkeyVAO);
    glGenBuffers(1, &monkeyVBO);

    glBindVertexArray(monkeyVAO);
    glBindBuffer(GL_ARRAY_BUFFER, monkeyVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vMonkey.size(), &vMonkey[0], GL_STATIC_DRAW);

    // position attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attributes
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), (void*)(sizeof(glm::vec3)));
    glEnableVertexAttribArray(1);

    // light
    std::vector<glm::vec3> vLight;
    std::vector<int> iLight;
    ObjFileParser parseCube(std::make_unique<File>("../models/quader.obj"));
    parseCube.Parse();
    parseCube.GetVerticesOpenGL(vLight, iLight);

    unsigned int lightVAO, lightVBO;
    glGenVertexArrays(1, &lightVAO);
    glGenBuffers(1, &lightVBO);

    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vLight.size(), &vLight[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3) ,(void*)0);
    glEnableVertexAttribArray(0);
    // -------------------------------------------------------------------------------------------
    lightingShader.use(); // don't forget to activate/use the shader before setting uniforms!
   // pass projection matrix to shader (as projection matrix rarely changes there's no need to do this per frame)
    // -----------------------------------------------------------------------------------------------------------
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    lightingShader.setMat4("projection", projection);

    Camera cam;

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // cam.ProcessInput(window, deltaTime);

        processInput(window);
        cam.ProcessInput(window, 0.001);
        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        lightingShader.use();
        lightingShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        lightingShader.setVec3("lightPos", lightPos);

        // camera/view transformation
         glm::mat4 view = cam.GetViewMatrix();
        // glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        lightingShader.setMat4("view", view);
        glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        lightingShader.setMat4("model", model);

        // render container
        glBindVertexArray(monkeyVAO);
        glDrawArrays(GL_TRIANGLES, 0, vMonkey.size() / 2);

        // draw the lamp
        lampShader.use();
        lampShader.setMat4("projection", projection);
        lampShader.setMat4("view",view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f));
        lampShader.setMat4("model", model);

        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, vLight.size());
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------

        glBindVertexArray(0);
        glUseProgram(0);
    
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &monkeyVAO);
    glDeleteBuffers(1, &monkeyVBO);

    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &lightVBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = 2.5 * deltaTime; 
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}
 



void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}