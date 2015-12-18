cmake_minimum_required (VERSION 2.6)
project (wubwub)
find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)

set (GL_LIBRARY GL GLU X11 GLEW Xxf86vm Xrandr pthread Xi Xinerama Xcursor) 
set (CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")

add_executable(wubwub hello.cpp)

target_link_libraries(wubwub glfw3 ${GL_LIBRARY})
