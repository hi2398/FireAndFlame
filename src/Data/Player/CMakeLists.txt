cmake_minimum_required(VERSION 3.11)

add_library(Player STATIC PlayerCharacter.h PlayerCharacter.cpp PlayerObserver.cpp PlayerObserver.h MovementState.cpp MovementState.h ActionState.cpp ActionState.h MovingGroundedSubState.cpp MovingGroundedSubState.h IdleGroundedSubState.cpp IdleGroundedSubState.h FallingSubState.cpp FallingSubState.h JumpingSubState.cpp JumpingSubState.h)
target_link_libraries(Player raylib Observer Core Scenes Data)