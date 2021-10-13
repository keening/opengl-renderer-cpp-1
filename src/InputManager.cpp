#include <InputManager.hpp>
#include <iostream>

InputManager::InputManager() : mouseX(0), mouseY(0) {}

InputManager::~InputManager() {}

void InputManager::PollEvents() 
{
    // We clear the previous relative motion values, preventing drift.
    this->mouseX = 0, this->mouseY = 0;

    while (SDL_PollEvent(&this->mainEvent))
    {
        switch (mainEvent.type)
        {
            case SDL_KEYDOWN:
                this->HandleKeys(this->mainEvent.key.keysym.sym);
                break;
            
            case SDL_MOUSEMOTION:
                this->HandleMouse(mainEvent.motion);
                break;

            case SDL_QUIT:
                // Temporary quit function, write a custom one.
                SDL_Quit();
                break;

            default:
                break;
        }
    }
}

void InputManager::HandleMouse(SDL_MouseMotionEvent& motion)
{
    this->mouseX = motion.xrel;
    this->mouseY = motion.yrel;
}

void InputManager::HandleKeys(SDL_Keycode keyCode)
{
    //CODE
}