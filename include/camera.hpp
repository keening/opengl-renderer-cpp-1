#include <glm/glm.hpp>

class InputManager;

class Camera {
    public:
        Camera();
        ~Camera();

        
        void ProcessInput(float delta);
        void HandleMouse();

        void SetController(InputManager controller);
        InputManager* GetController() { return this->cameraController; }
        glm::vec3 GetPosVec()   { return position; }
        glm::vec3 GetFrontVec() { return front; }
        glm::vec3 GetUpVec()    { return up; }

    private:
        InputManager* cameraController;

        glm::vec3 position, front, up, right;
        float yaw, pitch, speed, fov, sensitivity, velocity;
};