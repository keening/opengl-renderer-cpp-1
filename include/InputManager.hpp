#pragma once
#include <SDL2/SDL.h>

class InputManager {
    public:
        InputManager();
        ~InputManager();

        void PollEvents();
        void HandleMouse(SDL_MouseMotionEvent& motion);
        void HandleKeys(SDL_Keycode keycode);

        int GetMouseX() { return this->mouseX; }
        int GetMouseY() { return this->mouseY; }
        
    private:
        SDL_Event mainEvent;
        int mouseX, mouseY;
    };