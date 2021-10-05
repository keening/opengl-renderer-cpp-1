#include <camera.hpp>
#include <SDL.h>

camera::camera() 
{
    this->position = glm::vec3(0.0f, 0.0f, 3.0f);
    this->front = glm::vec3(0.0f, 0.0f, -1.0f);
    this->up = glm::vec3(0.0f, 1.0f, 0.0f);
}

camera::~camera() {}

void camera::handle_input(float delta) 
{
    SDL_Event event;
    this->speed = 10.0f * delta;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_UP:
                        this->position += this->speed * this->front;
                        break;
                    case SDLK_DOWN:
                        this->position -= this->speed * this->front;
                        break;
                    case SDLK_LEFT:
                        this->position -= this->speed * glm::normalize(
                            glm::cross(this->front, this->up));
                        break;
                    case SDLK_RIGHT:
                        this->position += this->speed * glm::normalize(
                            glm::cross(this->front, this->up));
                        break;
                    default:
                        break;
                }
        }
    }
}