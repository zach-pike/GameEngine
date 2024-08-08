cmake_minimum_required(VERSION 3.22.1)

project(GLLearning)

set(IMGUI_SOURCE 
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui.cpp
    imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_opengl3.cpp
)
add_library(IMGui STATIC ${IMGUI_SOURCE})
target_include_directories(IMGui AFTER PUBLIC ./imgui/)
target_include_directories(IMGui AFTER PUBLIC ./)

add_subdirectory(src/)
add_subdirectory(lib/)