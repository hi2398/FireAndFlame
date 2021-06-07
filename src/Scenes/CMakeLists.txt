cmake_minimum_required(VERSION 3.11)
add_library(Scenes STATIC MainMenu.h MainMenu.cpp NeutralArea.cpp NeutralArea.h)
target_link_libraries(Scenes raylib)