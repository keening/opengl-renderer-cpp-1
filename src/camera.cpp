#include <camera.hpp>
#include <SDL2/SDL.h>

camera::camera(int sw, int sh) : yaw(-90.0f), fov(45.0f), 
    is_initial_move(true), sens(0.1f), speed(2.5f)
{
    this->position = glm::vec3(0.0f, 0.0f, 3.0f);
    this->front = glm::vec3(0.0f, 0.0f, -1.0f);
    this->up = glm::vec3(0.0f, 1.0f, 0.0f);
    this->last_x = sw / 2.0f;
    this->last_y = sh / 2.0f;
}

camera::~camera() {}

void camera::handle_input(float delta) 
{
    SDL_Event event;
    this->velocity = this->speed * delta;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_UP:
                        this->position += this->front * this->velocity;
                        break;
                    case SDLK_DOWN:
                        this->position -= this->front * this->velocity;
                        break;
                    case SDLK_LEFT:
                        this->position -= this->right * this->velocity;
                        break;
                    case SDLK_RIGHT:
                        this->position += this->right * this->velocity;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_MOUSEMOTION:
                handle_mouse(event);
                break;
        }
    }
}

void camera::handle_mouse(SDL_Event e)
{
    if (this->is_initial_move)
    {
        last_x = e.motion.x;
        last_y = e.motion.y;
        this->is_initial_move = false;
    }

    int x_offset = e.motion.x - last_x;
    int y_offset = last_y - e.motion.y;
    last_x = e.motion.x;
    last_y = e.motion.y;
    x_offset *= sens;
    y_offset *= sens;
    this->yaw += x_offset;
    this->pitch += y_offset;

    if (this->pitch > 89.0f)
        this->pitch = 89.0f;
    if (this->pitch < -89.0f)
        this->pitch = -89.0f;

    glm::vec3 tmp;
    tmp.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    tmp.y = sin(glm::radians(this->pitch));
    tmp.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    this->front = glm::normalize(tmp);
    this->right = glm::normalize(glm::cross(this->front, glm::vec3(0.0f, 1.0f, 0.0f)));
    this->up = glm::normalize(glm::cross(this->right, this->front));

}