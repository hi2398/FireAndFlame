cmake_minimum_required(VERSION 3.11)


add_library(Enemies STATIC Miner.h Miner.cpp ToastCat.h ToastCat.cpp "IdleState.h" "IdleState.cpp" "ApproachingState.h" "ApproachingState.cpp" "AttackingState.h" "AttackingState.cpp" "RoamingState.h" "RoamingState.cpp" "EnemyStateHandler.h" "EnemyStateHandler.cpp" "StunnedState.h" "StunnedState.cpp" "Howler.h" "Howler.cpp" "Fly.h" "Fly.cpp")
target_link_libraries(Enemies raylib Core Player Scenes Observer Data)