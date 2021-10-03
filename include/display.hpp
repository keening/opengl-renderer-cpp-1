#pragma once
#include <SDL.h>

class display 
{
public:
    display();
    ~display();

    void setup();
    void present();
    int get_width() { return window_width; }
    int get_height() { return window_height; }

private:
    void init();

    SDL_Window *window;
    SDL_GLContext gl_context;
    
    const char *window_title = "OpenGL Renderer";
    int window_width = 1280, window_height = 720;
};