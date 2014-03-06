project(Testcomp)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)

file(GLOB RES_FILES *.frag *.vert)

include_directories("include/")

link_directories (${Testcomp_BINARY_DIR}/lib) 

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(ALL_LIBS
            GL
            glfw
            GLEW
    )
    SET(GCC_COMPILE_FLAGS "-std=c++11")
    SET(GCC_COMPILE_FLAGS2 "--verbose")
    SET(GCC_LINK_FLAGS2    "--verbose")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(ALL_LIBS
            GLEW_190
            GLFW_276
            opengl32
    )
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

add_definitions(${GCC_COMPILE_FLAGS})

add_executable(test_executable
        test.c
        ${RES_FILES}
)

target_link_libraries(test_executable
        ${ALL_LIBS}
)

# gcc test.c lib/libglfw.a -lXrandr -lX11 -pthread -lm -lGLU -lGL -lGLEW -o test

