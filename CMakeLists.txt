cmake_minimum_required(VERSION 3.10)
project(renderer)

set(LIBRARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor)
set(GLAD_DIR ${LIBRARY_DIR}/glad)
set(STB_DIR ${LIBRARY_DIR}/stb)
set(glm_DIR ${LIBRARY_DIR}/glm/cmake/glm)
set(STB_DIR ${LIBRARY_DIR}/stb)
set(SDL2_DIR ${LIBRARY_DIR}/sdl2)

set(SOURCES
    src/main.cpp
    src/Window.cpp
    src/Shader.cpp
    src/Mesh.cpp
    src/Texture.cpp
    src/Application.cpp
    src/Camera.cpp
    src/InputManager.cpp
    ${GLAD_DIR}/src/glad.c
    )
set(HEADERS
    include/window.hpp
    include/shader.hpp
    include/Mesh.hpp
    include/Texture.hpp
    include/Application.hpp
    include/Camera.hpp
    include/InputManager.hpp
    ) 
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${SDL2_DIR}/include
    ${GLAD_DIR}/include
    ${GLM_DIR}/glm
    ${LIBRARY_DIR}
    )
link_directories(${SDL2_DIR}/lib)
add_executable(
    renderer 
    ${SOURCES} 
    ${HEADERS}
    )
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
target_link_libraries(renderer SDL2main SDL2 glm::glm)