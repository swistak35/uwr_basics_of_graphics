project(zadanie3)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)

include_directories(
    includes/
    .
)

link_directories(
    libs/
)

SET(GCC_COMPILE_FLAGS "-std=c++11")
#SET(GCC_LINK_FLAGS    "")
add_definitions(${GCC_COMPILE_FLAGS})

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(ALL_LIBS
            GL
            glfw
            GLEW
    )
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(ALL_LIBS
            GLEW_190
            GLFW_276
            opengl32
    )
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

add_executable(arkanoid
        main.cpp
        shader.cpp
        shader.hpp
        graphics_class.cpp
        graphics_class.hpp
        arkanoid_game.cpp
        arkanoid_game.hpp
)

target_link_libraries(arkanoid
        ${ALL_LIBS}
)


