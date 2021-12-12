cmake_minimum_required(VERSION 3.14)
project(mp)
set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES main.cpp Engine.cpp Engine.hpp
        ArcCam.hpp ArcCam.cpp FPCam.hpp FPCam.cpp
        Steve.hpp Steve.cpp
        Block.cpp Block.hpp
        Chunk.cpp Chunk.hpp
        TextureManager.cpp TextureManager.hpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Windows with MinGW Installations
if( ${CMAKE_SYSTEM_NAME} MATCHES "Windows" AND MINGW )
    # if working on Windows but not in the lab
    # update the include directory location
    include_directories("Z:/CSCI441/include")
    # update the lib directory location
    target_link_directories(${PROJECT_NAME} PUBLIC "Z:/CSCI441/lib")
    target_link_libraries(${PROJECT_NAME} opengl32 glfw3 glew32.dll gdi32)
# OS X Installations
elseif( APPLE AND ${CMAKE_SYSTEM_NAME} MATCHES "Darwin" )
    # update the include directory location
    include_directories("/usr/local/include")
    # update the lib directory location
    target_link_directories(${PROJECT_NAME} PUBLIC "/usr/local/lib")
    target_link_directories(${PROJECT_NAME} PUBLIC "./include")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL" "-framework Cocoa" "-framework IOKit" "-framework CoreVideo" glfw3 glew)
# Blanket *nix Installations
elseif( UNIX AND ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )
    include_directories("/usr/local/include")
    include_directories("./include/")
    include_directories("/home/keith/Coding/Computer Graphics/include")
    # update the lib directory location
    target_link_directories(${PROJECT_NAME} PUBLIC "/usr/local/lib")
    target_link_directories(${PROJECT_NAME} PUBLIC "/usr/lib64")
    target_link_libraries(${PROJECT_NAME} OpenGL glfw GLEW)


endif()
