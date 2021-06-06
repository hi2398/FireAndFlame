cmake_minimum_required(VERSION 3.11)
add_executable(Scenes MainMenu.h MainMenu.cpp NeutralArea.cpp NeutralArea.h TestScene.cpp TestScene.h)
target_link_libraries(Scenes raylib)