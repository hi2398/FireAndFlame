cmake_minimum_required(VERSION 3.11)
add_library(Scenes STATIC MainMenu.h MainMenu.cpp NeutralArea.cpp NeutralArea.h AreaOne.cpp AreaOne.h SceneEnums.h DeathScreen.cpp DeathScreen.h IceBossScene.cpp IceBossScene.h Tutorial.cpp Tutorial.h FinalBoss.cpp FinalBoss.h)
target_link_libraries(Scenes raylib Core Observer Player Data Enemies IceBoss)