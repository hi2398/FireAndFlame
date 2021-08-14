cmake_minimum_required(VERSION 3.11)

add_library(TraitorBoss STATIC TraitorBoss.h TraitorBoss.cpp   "TBAfterFightState.h" "TBAfterFightState.cpp" "TBBeforeFightState.h" "TBBeforeFightState.cpp" "TBIdleState.h" "TBIdleState.cpp"   "TBMeleeState.h" "TBMeleeState.cpp" "TBRangedState.h" "TBRangedState.cpp" "TBSeekCoal.h" "TBSeekCoal.cpp" "TBApproachingState.h" "TBApproachingState.cpp" "TBJumpUpStage.h" "TBJumpUpStage.cpp")
target_link_libraries(TraitorBoss Enemies raylib Core Player Scenes Data)