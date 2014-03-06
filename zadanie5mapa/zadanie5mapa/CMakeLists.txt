project(zadanie5mapa)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)

# Dodanie plików shaderów jako pliki projektu
file(GLOB RES_FILES *.frag *.vert)

# Ścieżki do katalogów z nagłówkami i bibliotekami
include_directories("include/")
link_directories (${zadanie5mapa_SOURCE_DIR}/lib)

# Wymagane przez glew
add_definitions( -DGLEW_STATIC )

# OpenGL
find_package(OpenGL REQUIRED)

set(ALL_LIBS
  ${OPENGL_LIBRARY}
  glfw
  GLEW
)

# W vs2010 usuwa to projekt ZERO_CHECK z solution.
# Odkomentować tylko jeśli nie zamierzamy użyć cmake więcej niż raz w tym projekcie
# set(CMAKE_SUPPRESS_REGENERATION TRUE)

# C++11
list(APPEND CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} --verbose")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    # Working dir
    # Nie działa, bo trzebaby dorzucić dodatkowe moduły, patrz CMake z openGL tutoriala
    # create_target_launcher(Tutorial02 WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

add_executable(zadanie5mapa
        main.cpp
        utils.hpp
        utils.cpp
        shader.hpp
        shader.cpp
        graphics_class.hpp
        graphics_class.cpp
        globe_class.hpp
        globe_class.cpp
        observer_class.hpp
        observer_class.cpp
        ${RES_FILES}
)

target_link_libraries(zadanie5mapa
        ${ALL_LIBS}
)

