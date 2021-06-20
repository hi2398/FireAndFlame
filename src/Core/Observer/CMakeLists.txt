cmake_minimum_required(VERSION 3.11)

add_library(Observer STATIC Observer.h Observer.cpp Events.h)
target_link_libraries(Observer raylib)