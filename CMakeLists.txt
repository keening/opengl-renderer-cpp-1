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
    src/display.cpp
    src/shader.cpp
    src/mesh.cpp
    src/texture.cpp
    src/application.cpp
    src/camera.cpp
    ${GLAD_DIR}/src/glad.c
    )
set(HEADERS
    include/display.hpp
    include/shader.hpp
    include/mesh.hpp
    include/texture.hpp
    include/application.hpp
    include/camera.hpp
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