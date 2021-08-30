cmake_minimum_required(VERSION 3.11)

add_subdirectory(TraitorBoss)
add_subdirectory(Player)
add_subdirectory(IceBoss)
add_subdirectory(Enemies)

add_library(Data STATIC Coal.h Coal.cpp HUD.h HUD.cpp SceneChangerObject.cpp SceneChangerObject.h DialogueObject.cpp DialogueObject.h FinalBoss/SpearAttack.cpp FinalBoss/SpearAttack.h FinalBoss/ChasingBoss.cpp FinalBoss/ChasingBoss.h FinalBoss/EnergyAttack.cpp FinalBoss/EnergyAttack.h FinalBoss/FBIdleFly.cpp FinalBoss/FBIdleFly.h FinalBoss/FBFlyDown.cpp FinalBoss/FBFlyDown.h FinalBoss/FBSpawnE.cpp FinalBoss/FBSpawnE.h FinalBoss/FBSpearAtk.cpp FinalBoss/FBSpearAtk.h FinalBoss/FBSwordAtk.cpp FinalBoss/FBSwordAtk.h FinalBoss/FBEnergyAtk.cpp FinalBoss/FBEnergyAtk.h FinalBoss/FBIdleDown.cpp FinalBoss/FBIdleDown.h FinalBoss/FBBigSpearAtk.cpp FinalBoss/FBBigSpearAtk.h FinalBoss/FBSpawnEDown.cpp FinalBoss/FBSpawnEDown.h FinalBoss/FinalBossEnemy.cpp FinalBoss/FinalBossEnemy.h FinalBoss/BossSword.cpp FinalBoss/BossSword.h FinalBoss/BossEnergySwordAttack.cpp FinalBoss/BossEnergySwordAttack.h FinalBoss/FBBossDying.cpp FinalBoss/FBBossDying.h MinerBoss/MinerBoss.cpp MinerBoss/MinerBoss.h MinerBoss/MBPhaseTransitionState.cpp MinerBoss/MBPhaseTransitionState.h MinerBoss/MBMeleeAttackState.cpp MinerBoss/MBMeleeAttackState.h MinerBoss/MBRangedState.cpp MinerBoss/MBRangedState.h MinerBoss/MBSummonState.cpp MinerBoss/MBSummonState.h "HeartObject.h" "HeartObject.cpp" "TmpDialogueObject.h" "TmpDialogueObject.cpp" "Speechbubble.h" "Speechbubble.cpp" "MinerBoss/MBDecisionState.cpp"  "MinerBoss/MBDecisionState.h" "HitMarker.h" "HitMarker.cpp")

target_link_libraries(Data raylib Core Player Scenes Observer Enemies)