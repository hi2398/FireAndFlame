cmake_minimum_required(VERSION 3.11)

add_library(IceBoss STATIC IceBoss.h IceBoss.cpp)
target_link_libraries(IceBoss raylib Core Player Scenes Observer Data)