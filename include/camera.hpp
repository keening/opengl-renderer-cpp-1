#include <glm/glm.hpp>

class camera
{
    public:
        camera();
        ~camera();

        glm::vec3 get_pos() { return position; }
        glm::vec3 get_front() { return front; }
        glm::vec3 get_up() { return up; }
        void handle_input(float delta);
    private:
        glm::vec3 position, front, up;
        float speed;
};