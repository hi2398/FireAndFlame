#include "SceneManager.h"
#include <iostream>


SceneManager::SceneManager(std::shared_ptr<Scene> initialScene):
                           activeScene(std::move(initialScene)) {
    nextScene=activeScene;
}

void SceneManager::Tick() {
    activeScene = nextScene;


    activeScene->RemoveMarkedDelete(); //delete all enemies and interactables that have been marked for deletion
    
    playerController->HandleInput();

    playerCharacter->Update();

    for (const auto& enemy : activeScene->GetEnemies()){
        enemy->Update();
    }
    for (const auto& interactable : activeScene->GetInteractables()){
        interactable->Update();
    }

    activeScene->Update();
    hud->UpdateHUD();

    BeginMode2D(playerCharacter->camera);
    background->Draw();
    activeScene->GetTilemap()->Draw();

    for (const auto& enemy : activeScene->GetEnemies()){
        enemy->Draw();
    }
    for (const auto& interactable : activeScene->GetInteractables()) {
        interactable->Draw();
    }

	activeScene->Draw();
    if (playerCharacter->visible) playerCharacter->Draw();
	EndMode2D();

	hud->DrawHUD();

  playerCharacter->SetLastPosition(playerCharacter->GetPosition());
  activeScene->GetDialogueManager().DrawDialogue();
}

void SceneManager::SetNextScene(std::unique_ptr<Scene> nextScene) {
    this->nextScene=std::move(nextScene);
}

void SceneManager::SceneParallax(int direction) {
    //TODO: rework when actually implementing this stuff
    background->Parallax(direction);
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
    activeScene->GetDialogueManager().UpdateDialogue(filepath);
}
