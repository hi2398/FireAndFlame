cmake_minimum_required (VERSION 3.11)

project(FireAndFlame)

add_subdirectory ("src")
target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS" "/ENTRY:mainCRTStartup")