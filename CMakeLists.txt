cmake_minimum_required(VERSION 3.23)
project(opengl_prj)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Map=output.map")

# dependencies
find_package(OpenGL REQUIRED)
add_subdirectory("3rdparty/glm")
add_subdirectory("3rdparty/glfw")
add_subdirectory("3rdparty/assimp")

# for glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# for glew
set(GLEW_LIB_DIRS "D:/LIBS/glew-2.1.0/lib/Release/x64")
set(GLEW_INCLUDE_DIRS "D:/LIBS/glew-2.1.0/include")

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
target_link_directories(opengl_prj PUBLIC ${GLEW_LIB_DIRS}
                                        "3rdparty/lib")
target_include_directories(opengl_prj PUBLIC ${GLEW_INCLUDE_DIRS}
                                            "3rdparty")
target_link_libraries(opengl_prj OpenGL::GL glew32 glfw glm assimp)

