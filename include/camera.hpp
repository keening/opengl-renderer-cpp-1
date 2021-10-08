#include <glm/glm.hpp>
#include <display.hpp>

class camera
{
    public:
        camera();
        camera(int sw, int sh);
        ~camera();

        glm::vec3 get_pos() { return position; }
        glm::vec3 get_front() { return front; }
        glm::vec3 get_up() { return up; }
        void handle_input(float delta);
        void handle_mouse(SDL_Event e);
    private:
        glm::vec3 position, front, up, right;
        float yaw, pitch, speed, fov, last_x, last_y, sens, velocity;
        bool is_initial_move;
};