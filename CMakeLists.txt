cmake_minimum_required(VERSION 3.23)
project(opengl_prj)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE ON)

#if(MSVC)
#   set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
#   set(BUILD_SHARED_LIBS TRUE)
#endif()

# DEPENDENCIES
# for OpenGL
find_package(OpenGL)
if(OPENGL_FOUND)
    message(STATUS "OpenGL found, vesrion: ${OPENGL_VERSION}
     Library path: ${OPENGL_LIBRARIES}
     Include path: ${OPENGL_INCLUDE_PATH}")
else()
    message(FATAL_ERROR "OpenGL not found. Please, install it and try again")
endif()

# Assimp, glm,
add_subdirectory("3rdparty/glm")
add_subdirectory("3rdparty/assimp")
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)

# for glfw
add_subdirectory("3rdparty/glfw")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)

# for glew
set(GLEW_LIB_DIR "D:/LIBS/glew-2.1.0/lib/Release/Win32") # you can specify your GLEW PATH here
set(GLEW_INCLUDE_DIR "D:/LIBS/glew-2.1.0/include")
list(APPEND CMAKE_PREFIX_PATH ${GLEW_LIB_DIR} ${GLEW_INCLUDE_DIR})
message(STATUS "CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
find_package(GLEW)
if(GLEW_FOUND)
    get_filename_component(GLEW_LIB_DIR ${GLEW_SHARED_LIBRARY} DIRECTORY)
    message(STATUS "Glew found, version: ${GLEW_VERSION}
     Library path: ${GLEW_SHARED_LIBRARY}
     Library dir: ${GLEW_LIB_DIR}
     Include path: ${GLEW_INCLUDE_DIR}")
else()
    message(FATAL_ERROR "Try to set manualy GLEW_INCLUDE_DIR GLEW_LIB_DIR")
endif()


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
target_link_directories(opengl_prj PUBLIC ${GLEW_LIB_DIR}
                                        "3rdparty/lib")
target_include_directories(opengl_prj PUBLIC ${GLEW_INCLUDE_DIR}
                                            "3rdparty")
target_link_libraries(opengl_prj OpenGL::GL glew32 glfw glm assimp)

