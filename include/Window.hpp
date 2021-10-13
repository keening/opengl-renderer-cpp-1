#pragma once
#include <SDL2/SDL.h>

class Window {
    public:
        Window();
        ~Window();

        void Setup();
        void Present();
        void Clear();

        int GetWidth() { return this->width; }  
        int GetHeight() { return this->height; }  

    private:
        SDL_Window *sdlWindow;
        SDL_GLContext glContext;
        
        const char *title = "APOLLO ENGINE";
        int width = 1280, height = 720;
};