cmake_minimum_required(VERSION 3.11)

add_library(Player STATIC PlayerCharacter.h PlayerCharacter.cpp PlayerObserver.cpp PlayerObserver.h)
target_link_libraries(Player raylib)