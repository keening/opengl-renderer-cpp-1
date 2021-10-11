#include <application.hpp>
#include <shader.hpp>
#include <mesh.hpp>
#include <texture.hpp>
#include <camera.hpp>

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

application::application() : is_running(true) {}

application::~application() {}

void application::main_loop()
{
    shader box_shader("../shaders/box_vert.glsl", "../shaders/box_frag.glsl");
    shader lamp_shader("../shaders/lamp_vert.glsl", "../shaders/lamp_frag.glsl");

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
    
    mesh box(cube_verts);
    mesh lamp(cube_verts);
    //texture t("../assets/default.jpg");

    box_shader.use();

    camera cam(d.get_width(), d.get_height());
    float current_frame, delta_time, last_frame;

    glm::vec3 light_pos(1.2f, 1.0f, 2.0f);

    while (this->is_running) 
    {            
        current_frame = SDL_GetTicks() / 1000.0f;
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        cam.handle_input(delta_time);
        d.clear();

        box_shader.use();
        box_shader.set_vec3("object_color", glm::vec3(1.0f, 0.5f, 0.31f));
        box_shader.set_vec3("light_color", glm::vec3(1.0f, 1.0f, 1.0f));

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)d.get_width() / (float)d.get_height(), 0.1f, 100.0f);
        glm::mat4 view = glm::lookAt(cam.get_pos(), cam.get_pos() + cam.get_front(), cam.get_up());
        box_shader.set_mat4("projection", projection); 
        box_shader.set_mat4("view", view);

        glm::mat4 model = glm::mat4(1.0f);
        box_shader.set_mat4("model", model);
        
        box.draw();

        lamp_shader.use();
        lamp_shader.set_mat4("projection", projection); 
        lamp_shader.set_mat4("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, light_pos);
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
        lamp_shader.set_mat4("model", model);

        lamp.draw();
        d.present();
    }
}