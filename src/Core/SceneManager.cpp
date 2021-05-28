//
// Created by Adrian on 28/05/2021.
//

#include "SceneManager.h"

SceneManager::SceneManager(std::unique_ptr<Scene> initialScene) : activeScene(std::move(initialScene)), nextScene(activeScene){

}

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
