//
// Created by Adrian on 28/05/2021.
//

#include "SceneManager.h"

SceneManager::SceneManager(std::unique_ptr<Scene> initialScene, std::unique_ptr<GameMode> gameMode)
    : activeScene(std::move(initialScene)), nextScene(activeScene), gameMode(std::move(gameMode)){}

void SceneManager::Tick() {
    activeScene=nextScene;
    gameMode->getPlayerController()->HandleInput();
    gameMode->getPlayerCharacter()->Update();
    gameMode->getPlayerCharacter()->Draw();
    activeScene->Update();
    activeScene->Draw();
}

void SceneManager::SetNextScene(std::unique_ptr<Scene> nextScene) {
    this->nextScene=std::move(nextScene);
}
