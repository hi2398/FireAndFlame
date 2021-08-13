cmake_minimum_required(VERSION 3.11)

add_library(TraitorBoss STATIC TraitorBoss.h TraitorBoss.cpp TraitorStateHandler.h TraitorStateHandler.cpp "TBAfterFightState.h" "TBAfterFightState.cpp" "TBBeforeFightState.h" "TBBeforeFightState.cpp")
target_link_libraries(TraitorBoss Enemies raylib Core Player Scenes Data)