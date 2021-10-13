#include <Application.hpp>
#include <Shader.hpp>
#include <Mesh.hpp>
#include <Texture.hpp>
#include <Camera.hpp>
#include <InputManager.hpp>

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Application::Application() : isRunning(true) {}

Application::~Application() {}

void Application::MainLoop()
{
    InputManager mainInput;
    Shader box_shader("../shaders/box_vert.glsl", "../shaders/box_frag.glsl");
    Shader lamp_shader("../shaders/lamp_vert.glsl", "../shaders/lamp_frag.glsl");

    std::vector<float> cube_verts = 
    {
         -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    
    Mesh box(cube_verts);
    Mesh lamp(cube_verts);
    //texture t("../assets/default.jpg");

    box_shader.Use();

    Camera freeCam;
    freeCam.SetController(mainInput);
    float currentFrame, deltaTime, lastFrame;

    glm::vec3 light_pos(1.2f, 1.0f, 2.0f);

    while (this->isRunning) 
    {            
        currentFrame = SDL_GetTicks() / 1000.0f;
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;


        mainWindow.Clear();

        box_shader.Use();
        box_shader.SetVec3("object_color", glm::vec3(1.0f, 0.5f, 0.31f));
        box_shader.SetVec3("light_color", glm::vec3(1.0f, 1.0f, 1.0f));

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 
                               (float)mainWindow.GetWidth() / (float)mainWindow.GetHeight(), 
                               0.1f, 100.0f);

        glm::mat4 view = glm::lookAt(freeCam.GetPosVec(), freeCam.GetPosVec() + freeCam.GetFrontVec(), freeCam.GetUpVec());
        box_shader.SetMat4("projection", projection); 
        box_shader.SetMat4("view", view);

        glm::mat4 model = glm::mat4(1.0f);
        box_shader.SetMat4("model", model);
        
        box.Draw();

        lamp_shader.Use();
        lamp_shader.SetMat4("projection", projection); 
        lamp_shader.SetMat4("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, light_pos);
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
        lamp_shader.SetMat4("model", model);

        lamp.Draw();
        freeCam.ProcessInput(deltaTime);
        mainWindow.Present();
    }
}