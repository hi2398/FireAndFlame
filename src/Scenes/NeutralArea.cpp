#include "NeutralArea.h"
#include "raylib.h"
#include "../Core/EnemyList.h"
#include "../Data/NPC.h"
#include "raymath.h"
#include "../Data/Deathzone.h"
#include "../Data/SaveInteractable.h"


NeutralArea::NeutralArea(SceneEnums lastScene) : Scene(SceneEnums::NeutralArea){
    this->lastScene = lastScene;
    playerCharacter->active = true;
    playerCharacter->SetHealth(100);
    tilemap=std::make_unique<Tilemap>("assets/Tilemaps/Testmap/Tilemap_1.json","assets/Tilemaps/Neutral_Area_Tilemap.json");
    interactables.emplace_back(std::make_unique<Coal>(playerCharacter->GetPosition()));

    sceneChanger = LoadTexture("assets/graphics/OtherObjects/environment.png");

    Vector2 tempVec= {113*32,86*32};
    if (playerCharacter->GetUnlockedAbilities() == AbilitiesUnlocked::Dash)interactables.emplace_back(std::make_unique<SceneChangerObject>(tempVec,SceneEnums::AreaOne, sceneName));
    tempVec= {7*32,77*32};
    if (playerCharacter->GetUnlockedAbilities() == AbilitiesUnlocked::Walljump)interactables.emplace_back(std::make_unique<SceneChangerObject>(tempVec,SceneEnums::AreaTwo, sceneName));
    tempVec= {79*32,65*32};
    if (playerCharacter->GetUnlockedAbilities() == AbilitiesUnlocked::Doublejump)interactables.emplace_back(std::make_unique<SceneChangerObject>(tempVec,SceneEnums::AreaThree, sceneName));

    tempVec = {-200, 130*32};
    interactables.emplace_back(std::make_unique<Deathzone>(tempVec));

    tempVec = {59*32,101*32+6};
    statueTex = LoadTexture("assets/graphics/statue.png");
    interactables.emplace_back(std::make_unique<DialogueObject>("assets/Dialogues/Neutrale_Ebene_Statue.json",tempVec,statueTex));

    tempVec = {69*32,102*32+3};
    statueTex = LoadTexture("assets/graphics/Sign.png");
    interactables.emplace_back(std::make_unique<DialogueObject>("assets/Dialogues/Neutrale_Ebene_Level_12.json",tempVec,statueTex));

    tempVec = {55* 32, 103 * 32};
    spawner.emplace_back(std::make_unique<Spawner>(tempVec, SpawnerDirection::Up, SpawnerType::Coal, 600));
    tempVec = {104* 32, 102 * 32};
    spawner.emplace_back(std::make_unique<Spawner>(tempVec, SpawnerDirection::Left, SpawnerType::Coal, 600));
    tempVec = {26 * 32, 92 * 32};
    spawner.emplace_back(std::make_unique<Spawner>(tempVec, SpawnerDirection::Down, SpawnerType::Coal, 600));
    tempVec = {58* 32, 76*32};
    spawner.emplace_back(std::make_unique<Spawner>(tempVec, SpawnerDirection::Down, SpawnerType::Coal, 600));

    textureForegroundException = LoadTexture("assets/graphics/backgrounds/NeutralArea/Lower_Foreground.png");
    textureForegroundMain = LoadTexture("assets/graphics/backgrounds/NeutralArea/Upper_Foreground.png");
    textureBackgroundMain = LoadTexture("assets/graphics/backgrounds/NeutralArea/background.png");
    textureBackgroundException = LoadTexture("assets/graphics/backgrounds/NeutralArea/background.png");

    npc1Tex = LoadTexture("assets/graphics/NPCs/Npc1.png");
    npc2Tex = LoadTexture("assets/graphics/NPCs/Npc2.png");
    npc3Tex = LoadTexture("assets/graphics/NPCs/Npc3.png");
    npc4Tex = LoadTexture("assets/graphics/NPCs/Npc4.png");
    npc5Tex = LoadTexture("assets/graphics/NPCs/Npc5.png");

    interactables.emplace_back(std::make_unique<NPC>("assets/Dialogues/neutralAreaNPC1.json", npc1Pos, NPCType::one, "assets/Dialogues/neutralAreaNPC1.json"));
    interactables.emplace_back(std::make_unique<NPC>("assets/Dialogues/neutralAreaNPC2.json", npc2Pos, NPCType::two, "assets/Dialogues/neutralAreaNPC2.json"));
    interactables.emplace_back(std::make_unique<NPC>("assets/Dialogues/neutralAreaNPC3.json", npc3Pos, NPCType::three, "assets/Dialogues/neutralAreaNPC3.json"));
    interactables.emplace_back(std::make_unique<NPC>("assets/Dialogues/neutralAreaNPC4.json", npc4Pos, NPCType::four, "assets/Dialogues/neutralAreaNPC4.json"));
    interactables.emplace_back(std::make_unique<NPC>("assets/Dialogues/neutralAreaNPC5.json", npc5Pos, NPCType::five, "assets/Dialogues/neutralAreaNPC5.json"));

    speech.emplace_back(std::make_unique<Speechbubble>(npc1Pos));
    speech.emplace_back(std::make_unique<Speechbubble>(npc2Pos));
    speech.emplace_back(std::make_unique<Speechbubble>(npc3Pos));
    speech.emplace_back(std::make_unique<Speechbubble>(npc4Pos));
    speech.emplace_back(std::make_unique<Speechbubble>(npc5Pos));

    switch (lastScene)
    {
    case SceneEnums::MinerBoss:
        playerCharacter->SetPosition({ 86 * 32, 90 * 32 });
        foregroundPos = { 522 , -34.4 };
        backgroundPos = { 871, -604.8 };
        sceneChangerFrame1 = { 32 * 5, 0, 32 * 4, 32 * 4 };
        sceneChangerFrame2 = { 32, 0, -32 * 4, 32 * 4 };
        break;
    case SceneEnums::TraitorBoss:
        playerCharacter->SetPosition({ 37 * 32,73 * 32 });
        foregroundPos = { -422.4, -143.2 };
        backgroundPos = {-704, -1094.4 };
        sceneChangerFrame1 = { 32 * 5, 0, 32 * 4, 32 * 4 };
        sceneChangerFrame2 = { 32 * 5, 0, -32 * 4, 32 * 4 };
        break;
    default:
        playerCharacter->SetPosition(playerStart);
		foregroundPos = { 0,100 };
		backgroundPos = { 0,0 };
        sceneChangerFrame1 = {32, 0, 32 * 4, 32 * 4};
        sceneChangerFrame2 = { 32, 0, -32 * 4, 32 * 4 };
        break;
    }
    sceneChangerVec1 = { 111 * 32,86 * 32 };
    sceneChangerVec2 = { 9 * 32,77 * 32 };
    //fill background loop vector
	backgroundLoopX = 8;
	backgroundLoopY = 20;
	backgroundException = 0;

	foregroundLoopX = 4;
	foregroundLoopY = 8;
	foregroundException = 7;

	//checkpoints
	interactables.emplace_back(std::make_unique<SaveInteractable>(checkpointA));

    track = LoadMusicStream("assets/audio/tracks/NeutralArea.mp3");
    SetMusicVolume(track, soundManager->GetTrackVolume());
    PlayMusicStream(track);
}


void NeutralArea::Update() {
    UpdateMusicStream(track);
    Scene::Update();
    if (!activateShake) {
		if (lastScene == SceneEnums::MinerBoss || lastScene == SceneEnums::TraitorBoss) {
			sceneManager->ScreenShake(60);
            soundManager->PlaySfx(SFX::DOORS);
            activateShake = true;
		}
    }

    for (const auto& spawn : spawner) {
        spawn->Update();
        spawn->SpawnCoal();
    }

	for (const auto& bubble : speech) {
		bubble->Update();
	}

}

void NeutralArea::Draw() {
    Scene::Draw();
    DrawTextureRec(sceneChanger, sceneChangerFrame1, sceneChangerVec1, WHITE);
    DrawTextureRec(sceneChanger, sceneChangerFrame2, sceneChangerVec2, WHITE);
    DrawTextureRec(sceneChanger, { 32 * 5, 0, -32 * 4, 32 * 4 }, { 80 * 32, 87 * 32 }, WHITE);
    DrawTextureRec(sceneChanger, { 32 * 5, 0, -32 * 4, 32 * 4 }, { 33 * 32, 70 * 32 }, WHITE);
    DrawTextureRec(sceneChanger, {32, 0, 32 * 4, 32 * 4}, { 77 * 32, 65 * 32 }, WHITE);
    if constexpr (DEBUG_BUILD) {
        if (playerCharacter->GetCanDoubleJump()) {
			DrawText(TextFormat("DoubleJump ENABLED", playerCharacter->GetCanDash()), playerCharacter->GetPosition().x, playerCharacter->GetPosition().y - 100, 10, WHITE);
        }
        else {
            DrawText(TextFormat("DoubleJump DISABLED", playerCharacter->GetCanDash()), playerCharacter->GetPosition().x, playerCharacter->GetPosition().y - 100, 10, WHITE);
        }
    }
    for (const auto& spawn : spawner) {
        spawn->Draw();
    }
    for (const auto& bubble : speech) {
        bubble->Draw();
    }
}

NeutralArea::~NeutralArea() {
    UnloadTexture(textureBackgroundException);
    UnloadTexture(textureBackgroundMain);
    UnloadTexture(textureForegroundException);
    UnloadTexture(textureForegroundMain);
    UnloadTexture(sceneChanger);
    UnloadTexture(npc1Tex);
    UnloadTexture(npc2Tex);
    UnloadTexture(npc3Tex);
    UnloadTexture(npc4Tex);
    UnloadTexture(npc5Tex);
    UnloadTexture(statueTex);

    StopMusicStream(track);
    UnloadMusicStream(track);
}