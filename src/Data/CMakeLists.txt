cmake_minimum_required(VERSION 3.11)

add_library(Data STATIC Coal.h Coal.cpp HUD.h HUD.cpp PlayerCharacter.h PlayerCharacter.cpp)
target_link_libraries(Data raylib)