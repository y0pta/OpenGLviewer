cmake_minimum_required(VERSION 3.22)
project(opengl_prj)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE ON)
add_definitions(RESOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_compile_definitions(-DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake)
# DEPENDENCIES
find_package(OpenGL REQUIRED)
find_package(GLFW3 REQUIRED)
find_package(glm REQUIRED)
find_package(GLEW REQUIRED)
find_package(assimp REQUIRED)

#sources
set(SOURCES main.cpp
            3rdparty/stb/stb_image.cpp
            include/glfw_helpfunc.h
            include/Camera.cpp
            include/Camera.h
            include/Shader.h
            include/Shader.cpp
            include/Viewer.cpp
            include/Viewer.h
            include/Texture.cpp
            include/Texture.h
            include/Primitives.cpp
            include/Primitives.h
            include/Mesh.cpp
            include/Mesh.h
            include/glfw_helpfunc.cpp)

add_executable(opengl_prj ${SOURCES})

# Resources
#ADD_CUSTOM_TARGET(
#        copy_resources
#        ${CMAKE_COMMAND}
#        -D SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}
#        -D DESTINATION_DIR=${CMAKE_CURRENT_BINARY_DIR}
#        -P CopyResources.cmake
#        COMMENT "Copying Files for target" VERBATIM
#)
#ADD_DEPENDENCIES(opengl_prj copy_resources)
#file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shaders)
#file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/samples/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/samples)

message(STATUS "Binary dirs: ${CMAKE_CURRENT_BINARY_DIR}")
target_include_directories(opengl_prj PUBLIC "3rdparty")
# specify glm::glm
target_link_libraries(opengl_prj OpenGL::GL GLEW::GLEW glfw glm::glm assimp::assimp)

