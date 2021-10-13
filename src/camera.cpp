#include <Camera.hpp>
#include <InputManager.hpp>
#include <SDL2/SDL.h>
#include <iostream>

Camera::Camera() : yaw(-90.0f), fov(45.0f), sensitivity(0.1f), speed(2.5f)
{
    this->position = glm::vec3(0.0f, 0.0f, 3.0f);
    this->front = glm::vec3(0.0f, 0.0f, -1.0f);
    this->up = glm::vec3(0.0f, 1.0f, 0.0f);
}

Camera::~Camera() {}

void Camera::ProcessInput(float delta)
{
    cameraController->PollEvents();
    this->HandleMouse();
}   

void Camera::HandleMouse()
{
    this->yaw   += cameraController->GetMouseX() * this->sensitivity;
    this->pitch -= cameraController->GetMouseY() * this->sensitivity;

    if (this->pitch > 89.0f)
        this->pitch = 89.0f;
    if (this->pitch < -89.0f)
        this->pitch = -89.0f;

    glm::vec3 rotation;

    rotation.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    rotation.y = sin(glm::radians(this->pitch));
    rotation.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

    this->front = glm::normalize(rotation);
    this->right = glm::normalize(glm::cross(this->front, glm::vec3(0.0f, 1.0f, 0.0f)));
    this->up    = glm::normalize(glm::cross(this->right, this->front));
}

void Camera::SetController(InputManager controller)
{
    this->cameraController = &controller;
}