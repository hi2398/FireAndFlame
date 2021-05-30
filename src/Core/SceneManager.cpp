//
// Created by Adrian on 28/05/2021.
//

#include "SceneManager.h"

SceneManager::SceneManager(std::unique_ptr<Scene> initialScene, std::unique_ptr<GameMode> gameMode)
    : activeScene(std::move(initialScene)), gameMode(std::move(gameMode)){
    nextScene=activeScene;
}

void SceneManager::Tick() {
    activeScene=nextScene;
    gameMode->GetPlayerController()->HandleInput();
    gameMode->GetPlayerCharacter()->Update();
    gameMode->GetPlayerCharacter()->Draw();
    activeScene->Update();
    activeScene->Draw();
}

void SceneManager::SetNextScene(std::unique_ptr<Scene> nextScene) {
    this->nextScene=std::move(nextScene);
}
