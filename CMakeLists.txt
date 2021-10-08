cmake_minimum_required(VERSION 3.10)
project(renderer)

set(glm_DIR C:/deps/glm/cmake/glm)
set(SDL2_INCLUDE_DIR C:/deps/sdl2/include)
set(SDL2_LIB_DIR C:/deps/sdl2/lib/x64)
set(LIBRARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(GLAD_DIR ${LIBRARY_DIR}/glad)
set(STB_DIR ${LIBRARY_DIR}/stb)

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
    ${SDL2_INCLUDE_DIR}
    ${GLAD_DIR}/include
    ${GLM_DIR}/glm
    ${LIBRARY_DIR}
    )
link_directories(${SDL2_LIB_DIR})
add_executable(
    renderer 
    ${SOURCES} 
    ${HEADERS}
    )
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
target_link_libraries(renderer SDL2main SDL2 glm::glm)