#include <display.hpp>
#include <glad/glad.h>
#include <iostream>

display::display() 
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        exit(1);
    }
    else
    {
        this->window = SDL_CreateWindow(this->window_title,
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        this->window_width, this->window_height, SDL_WINDOW_OPENGL);
        if (!this->window)
        {
            std::cout << "Failed to create SDL window: " << SDL_GetError() << std::endl;
            exit(1);
        }
        else
        {
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, 
            SDL_GL_CONTEXT_PROFILE_CORE);

            this->gl_context = SDL_GL_CreateContext(this->window);
            if (!this->gl_context)
            {
                std::cout << "Failed to create GL context: " << SDL_GetError() << std::endl;
                exit(1);
            }
            else
            {
                if (!gladLoadGL())
                {
                    std::cout << "GLAD failed to load OpenGL." << std::endl;
                    exit(1);
                }
                else
                {
                    this->setup();
                }
            }
        }
    }
}

display::~display()
{
    SDL_Quit();
}

void display::setup()
{
    glViewport(0, 0, this->window_width, this->window_height);
    glEnable(GL_DEPTH_TEST);
}

void display::present() 
{
    SDL_GL_SwapWindow(this->window);
}

