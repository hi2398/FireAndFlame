#include <iostream>

#include "SceneManager.h"


SceneManager::SceneManager(std::shared_ptr<Scene> initialScene):
                           activeScene(std::move(initialScene)) {
    nextScene=activeScene;
}

void SceneManager::Tick() {
    BeginMode2D(playerCharacter->camera);
    activeScene=nextScene;
    playerController->HandleInput();
    if (playerCharacter->visible) {
		playerCharacter->Update();
		playerCharacter->Draw();
    }
    activeScene->Update();
    activeScene->Draw();
    hud->UpdateHUD();
    hud->DrawHUD();
    EndMode2D();
}

void SceneManager::SetNextScene(std::unique_ptr<Scene> nextScene) {
    this->nextScene=std::move(nextScene);
}
