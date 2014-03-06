project(zadanie2)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)

include_directories(
    includes/
    .
)

link_directories(
    libs/
)

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

add_executable(mastermind
        main.cpp
        shader.cpp
        shader.hpp
        vertex_data.hpp
        vertex_data.cpp
)

target_link_libraries(mastermind
        ${ALL_LIBS}
)
