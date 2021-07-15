#include "SceneManager.h"
#include <iostream>
#include <utility>
#include <iomanip>
#include "../json.hpp"
#include "../Global.h"

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
    int playerHealth =playerCharacter->GetHealth();
    Vector2 playerLocation = playerCharacter->GetPosition();


    json saveDataStruct = {
            {"player", //START PLAYER
                    {
                            {"health", playerHealth},
                            {"locationX", playerLocation.x},
                            {"locationY", playerLocation.y}
                    }
            } //END PLAYER
    };

    std::string saveSlot=saveFolder + "save" + "_" + std::to_string(slot) + ".json";

    //TODO: Copy old save over to prevent corruption
    std::ofstream saveFile{saveSlot};
    saveFile << std::setw(4) << saveDataStruct;
    saveFile.close();
}

void SceneManager::LoadGame(std::string saveFolder, int slot) {
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
        playerCharacter->SetPosition(location);
    }


    saveFile.close();
}

void SceneManager::Update(Vector2 virtualMousePosition) {
    activeScene = nextScene;
    this->virtualMousePosition = virtualMousePosition;

    if constexpr (DEBUG_BUILD) {
        if (IsKeyPressed(KEY_F8)) SaveGame("./", 69);
        if (IsKeyPressed(KEY_F9)) LoadGame("./", 69);
    }

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
    activeScene->Draw();
    activeScene->GetTilemap()->Draw();
    for (const auto& enemy : activeScene->GetEnemies()){
        enemy->Draw();
    }
    for (const auto& interactable : activeScene->GetInteractables()) {
        interactable->Draw();
    }
    if (playerCharacter->active) playerCharacter->Draw();
    EndMode2D();

    if (playerCharacter->active) hud->DrawHUD();


    activeScene->GetDialogueManager().DrawDialogue();

    //setting "last" values stay at the very end to prevent sequence errors
    playerCharacter->SetLastPosition(playerCharacter->GetPosition());
}

Vector2 SceneManager::GetVirtualMousePosition() {
    return virtualMousePosition;
}
