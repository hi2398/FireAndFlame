#include "SceneManager.h"
#include <iostream>


SceneManager::SceneManager(std::shared_ptr<Scene> initialScene):
                           activeScene(std::move(initialScene)) {
    nextScene=activeScene;
}

void SceneManager::Tick() {
    
    BeginMode2D(playerCharacter->camera);
	activeScene = nextScene;
    background->Draw();
    playerController->HandleInput();
	activeScene->Update();
	activeScene->Draw();
    if (playerCharacter->visible) {
		playerCharacter->Update();
		playerCharacter->Draw();
    }    
    EndMode2D();

    hud->UpdateHUD();
	hud->DrawHUD();
}

void SceneManager::SetNextScene(std::unique_ptr<Scene> nextScene) {
    this->nextScene=std::move(nextScene);
}

void SceneManager::SceneParallax(int direction)
{
    background->Parallax(direction);
}
