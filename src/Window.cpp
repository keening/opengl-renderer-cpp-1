#include <Window.hpp>

#include <glad/glad.h>
#include <iostream>

Window::Window() 
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        exit(1);
    }
    else
    {
        this->sdlWindow = SDL_CreateWindow(this->title,
                                           SDL_WINDOWPOS_UNDEFINED, 
                                           SDL_WINDOWPOS_UNDEFINED, 
                                           this->width, this->height, 
                                           SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        if (!this->sdlWindow)
        {
            std::cout << "Failed to create SDL Window: " << SDL_GetError() << std::endl;
            exit(1);
        }
        else
        {
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, 
                                SDL_GL_CONTEXT_PROFILE_CORE);

            this->glContext = SDL_GL_CreateContext(this->sdlWindow);

            SDL_SetWindowGrab(this->sdlWindow, SDL_TRUE);
            SDL_SetRelativeMouseMode(SDL_TRUE);

            if (!this->glContext)
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
                    this->Setup();
                }
            }
        }
    }
}

Window::~Window()
{
    SDL_Quit();
}

void Window::Setup()
{
    glViewport(0, 0, this->width, this->height);
    glEnable(GL_DEPTH_TEST);
}

void Window::Present() 
{
    SDL_GL_SwapWindow(this->sdlWindow);
}

void Window::Clear()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
