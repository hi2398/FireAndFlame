cmake_minimum_required(VERSION 3.11)

add_library(IceBoss STATIC IceBoss.h IceBoss.cpp IBSeek.cpp IBSeek.h IBMelee.cpp IBMelee.h IBRanged.cpp IBRanged.h IBMinions.cpp IBMinions.h IceZone.cpp IceZone.h "FreezeVisual.h" "FreezeVisual.cpp" "IBBeforeFight.h" "IBBeforeFight.cpp")
target_link_libraries(IceBoss raylib Core Player Scenes Observer Data ${PROJECT_NAME})