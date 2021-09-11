#include "SceneManager.h"
#include <iostream>
#include <utility>
#include <iomanip>
#include <filesystem>
#include "../json.hpp"
#include "../Global.h"
#include "../Scenes/NeutralArea.h"
#include "../Scenes/Tutorial.h"
#include "../Scenes/AreaOne.h"
#include "../Scenes/IceBossScene.h"
#include "../Scenes/AreaTwo.h"
#include "../Scenes/AreaThree.h"
#include "../Scenes/TraitorBossScene.h"
#include "../Scenes/FinalBoss.h"
#include "../Scenes/MinerBossScene.h"

using nlohmann::json;


SceneManager::SceneManager(std::shared_ptr<Scene> initialScene):
                           activeScene(std::move(initialScene)) {
    nextScene=activeScene;
}

void SceneManager::SetNextScene(std::unique_ptr<Scene> nextScene) {
    this->nextScene=std::move(nextScene);
}


const std::unique_ptr<Tilemap>& SceneManager::GetTilemap() {
    return activeScene->GetTilemap();
}

const std::list<std::unique_ptr<Interactable>> &SceneManager::GetInteractables() const {
    return activeScene->GetInteractables();
}

const std::list<std::unique_ptr<Enemy>> &SceneManager::GetEnemies() const {
    return activeScene->GetEnemies();
}

void SceneManager::UpdateDialogInScene(std::string filepath) {
    activeScene->GetDialogueManager().UpdateDialogue(std::move(filepath));
}

void SceneManager::SaveGame(std::string saveFolder, int slot) {
    if constexpr (DEBUG_BUILD){
        std::cout << "Saving to Slot " << slot << std::endl;
    }
    int playerHealth =playerCharacter->GetHealth();
    Vector2 playerLocation = playerCharacter->GetPosition();
    int unlockedAbilities = static_cast<int>(playerCharacter->GetUnlockedAbilities());
    int currentLevel = static_cast<int>(activeScene->GetSceneName());
    int hasPlayerKilledSaugi=playerCharacter->HasKilledSaugi();

    json saveDataStruct = {
            {"player", //START PLAYER
                    {
                            {"health", playerHealth},
                            {"locationX", playerLocation.x},
                            {"locationY", playerLocation.y},
                            {"unlockedAbilities", unlockedAbilities},
                            {"currentLevel", currentLevel},
                            {"cheese", hasPlayerKilledSaugi}
                    }
            } //END PLAYER
    };

    std::string saveSlot=saveFolder + "save" + "_" + std::to_string(slot) + ".json";
    std::string saveScreen=saveFolder + "save" + "_" + std::to_string(slot) + ".png";


    std::ifstream  src;
    std::ofstream  dst;
    switch (unlockedAbilities) {
        case 0:
            src.open("./assets/graphics/savegame/zero.png", std::ios::binary);
            dst.open(saveScreen, std::ios::binary);

            dst << src.rdbuf();
            break;
        case 1:
            src.open("./assets/graphics/savegame/one.png", std::ios::binary);
            dst.open(saveScreen, std::ios::binary);

            dst << src.rdbuf();
            break;
        case 2:
            src.open("./assets/graphics/savegame/two.png", std::ios::binary);
            dst.open(saveScreen, std::ios::binary);

            dst << src.rdbuf();
            break;
        case 3:
            src.open("./assets/graphics/savegame/three.png", std::ios::binary);
            dst.open(saveScreen, std::ios::binary);

            dst << src.rdbuf();
            break;
        default:
            break;
    }

     

    //TODO: Copy old save over to prevent corruption
    std::ofstream saveFile{saveSlot};
    saveFile << std::setw(4) << saveDataStruct;
    saveFile.close();
}

void SceneManager::LoadGame(std::string saveFolder, int slot) {

    if constexpr (DEBUG_BUILD){
        std::cout << "Loading from Slot " << slot << std::endl;
    }

    std::string saveSlot=saveFolder + "save" + "_" + std::to_string(slot) + ".json";
    std::ifstream saveFile{saveSlot};
    if (!saveFile) {
        std::cout
        << std::endl
        << "LOADING FAILED\n"
        << "LOADING FAILED\n"
        << "LOADING FAILED\n"
        << std::endl;
        return;
    }

    json saveDataStruct = json::parse(saveFile);


    for (const auto& category : saveDataStruct) {
        playerCharacter->SetHealth(category["health"]);
        Vector2 location{0, 0};
        location.x = category["locationX"];
        location.y = category["locationY"];
        playerPosToSet=location;
        setPlayerPos= true;
        playerCharacter->SetUnlockedAbilityLevel(static_cast<AbilitiesUnlocked>(category["unlockedAbilities"]));
        bool hasKilledSaugi=static_cast<bool>(category["cheese"]);
        if (hasKilledSaugi) playerCharacter->PlayerHasKilledSaugi();

        SceneEnums sceneToLoad=category["currentLevel"];
        switch (sceneToLoad) {


            case SceneEnums::NeutralArea:
                SetNextScene(std::make_unique<NeutralArea>(SceneEnums::Default));
                break;
            case SceneEnums::AreaOne:
                SetNextScene(std::make_unique<AreaOne>(SceneEnums::Default));
                break;
            case SceneEnums::Tutorial:
                SetNextScene(std::make_unique<Tutorial>(SceneEnums::Default));
                break;
            case SceneEnums::IceBoss:
                SetNextScene(std::make_unique<IceBossScene>(SceneEnums::Default));
                break;
            case SceneEnums::AreaTwo:
                SetNextScene(std::make_unique<AreaTwo>(SceneEnums::Default));
                break;
            case SceneEnums::AreaThree:
                SetNextScene(std::make_unique<AreaThree>(SceneEnums::Default));
                break;
            case SceneEnums::TraitorBoss:
                SetNextScene(std::make_unique<TraitorBossScene>(SceneEnums::Default));
                break;
            case SceneEnums::FinalBoss:
                SetNextScene(std::make_unique<FinalBoss>(SceneEnums::Default));
                break;
            case SceneEnums::MinerBoss:
                SetNextScene(std::make_unique<MinerBossScene>(SceneEnums::Default));
                break;
            case SceneEnums::Default:
                break;
        }
    }


    saveFile.close();
}

void SceneManager::ScreenShake(int durationInFrames)
{
    activeScene->ActivateScreenShake(durationInFrames);
}

void SceneManager::Update(Vector2 virtualMousePosition) {
    activeScene = nextScene;

    if (setPlayerPos){
        playerCharacter->SetPosition(playerPosToSet);
        setPlayerPos= false;
    }

    this->virtualMousePosition = virtualMousePosition;


    activeScene->RemoveMarkedDelete(); //delete all enemies and interactables that have been marked for deletion


    playerController->HandleInput();

    if (playerCharacter->active) playerCharacter->Update();


    for (const auto& enemy : activeScene->GetEnemies()){
        enemy->Update();
    }
    for (const auto& interactable : activeScene->GetInteractables()){
        interactable->Update();
    }

    activeScene->Update();
    hud->UpdateHUD();
}

void SceneManager::Draw() {
    if(playerCharacter->active) BeginMode2D(playerCharacter->camera);
    activeScene->DrawBackground();
    activeScene->GetTilemap()->Draw();
    activeScene->Draw();
    for (const auto& enemy : activeScene->GetEnemies()){
        enemy->Draw();
    }
    if (playerCharacter->active) playerCharacter->Draw();
    for (const auto& interactable : activeScene->GetInteractables()) {
        interactable->Draw();
    }
    activeScene->DrawForeground();
    EndMode2D();

    if (playerCharacter->active) hud->DrawHUD();


    activeScene->GetDialogueManager().DrawDialogue();


    //setting "last" values stay at the very end to prevent sequence errors
    playerCharacter->SetLastPosition(playerCharacter->GetPosition());
}

Vector2 SceneManager::GetVirtualMousePosition() {
    return virtualMousePosition;
}

void SceneManager::AddEnemy(std::unique_ptr<Enemy> enemy) {
    activeScene->AddEnemy(std::move(enemy));
}

void SceneManager::AddInteractable(std::unique_ptr<Interactable> interactable) {
    activeScene->AddInteractable(std::move(interactable));
}

void SceneManager::RemoveAllInteractables() {
    activeScene->RemoveInteractables();
}

std::shared_ptr<Scene> SceneManager::GetActiveScene() {
    return activeScene;
}

void SceneManager::SetActiveSaveSlot(int slot) {
    saveSlot=slot;
}

int SceneManager::GetSaveSlot() const{
    return saveSlot;
}

