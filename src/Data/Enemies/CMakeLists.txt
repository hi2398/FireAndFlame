cmake_minimum_required(VERSION 3.11)


add_library(Enemies STATIC Miner.h Miner.cpp ToastCat.h ToastCat.cpp "Howler.h" "Howler.cpp" "Fly.h" "Fly.cpp" "SpiderBot.h" "SpiderBot.cpp" "SpringHog.h" "SpringHog.cpp" "ApproachingState.h" "ApproachingState.cpp" "AttackingState.h" "AttackingState.cpp" "EnemyStateHandler.h" "EnemyStateHandler.cpp" "IdleState.h" "IdleState.cpp" "RoamingState.h" "RoamingState.cpp" "StunnedState.h" "StunnedState.cpp" "Saugi.h" "Saugi.cpp")
target_link_libraries(Enemies raylib Core Player Scenes Observer Data)