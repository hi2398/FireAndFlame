﻿cmake_minimum_required(VERSION 3.11)

include(../cmake/raylib.cmake)

project(FireAndFlame VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS -mwindows)
set(CMAKE_C_FLAGS -mwindows)






if (WIN32 AND (${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.20.0"))
    cmake_policy(SET CMP0115 OLD)
endif ()
if (UNIX AND NOT APPLE)
    cmake_policy(SET CMP0072 NEW)
endif ()


add_subdirectory(Core)
add_subdirectory(Scenes)
add_subdirectory(Data)
add_executable(${PROJECT_NAME} main.cpp config.h helper.h Global.h json.hpp)

# Add config.h.in file
configure_file(config.h.in config.h)
target_include_directories(${PROJECT_NAME} PUBLIC
        "${PROJECT_BINARY_DIR}"
        )

#  Link to Raylib
target_link_libraries(${PROJECT_NAME} raylib Scenes Core Data Player Observer)

# Copy assets to assets path
add_custom_target(copy_assets
        COMMAND ${CMAKE_COMMAND} -P "${CMAKE_CURRENT_LIST_DIR}/../cmake/copy-assets.cmake"
        )
add_dependencies(${PROJECT_NAME} copy_assets)

# CPack instructions
# call e.g. cpack -G ZIP -C Debug to create a binary distribution
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION "${PROJECT_NAME}_Bundle")
install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/assets" DESTINATION "${PROJECT_NAME}_Bundle")