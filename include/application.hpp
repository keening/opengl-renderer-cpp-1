#pragma once
#include <display.hpp>

class application
{
    public:
        application();
        ~application();
        void main_loop();

    private:
        display d;
        bool is_running = false;
};