#pragma once
#include <Window.hpp>

class Application
{
    public:
        Application();
        ~Application();
        void MainLoop();

    private:
        Window mainWindow;
        bool isRunning = false;
};