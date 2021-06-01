#include <iostream>

#include "SceneManager.h"


SceneManager::SceneManager(std::shared_ptr<Scene> initialScene):
                           activeScene(std::move(initialScene)) {
    nextScene=activeScene;
}

void SceneManager::Tick() {
    activeScene=nextScene;
    playerController->HandleInput();
    playerCharacter->Update();
    playerCharacter->Draw();
    activeScene->Update();
    activeScene->Draw();
    hud->UpdateHUD();
    hud->DrawHUD();
}

void SceneManager::SetNextScene(std::unique_ptr<Scene> nextScene) {
    this->nextScene=std::move(nextScene);
}
