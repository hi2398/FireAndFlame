#pragma once
#include <memory>
#include "Scene.h"
#include "GameMode.h"

class SceneManager {
public:
    explicit SceneManager(std::unique_ptr<Scene> initialScene, std::unique_ptr<GameMode> gameMode);
    SceneManager() = delete;
    void Tick();
    void SetNextScene(std::unique_ptr<Scene> nextScene);
protected:

private:
    //DO NOT CHANGE THE ORDER OF THESE POINTERS, WILL BREAK INITIALIZATION
    std::shared_ptr<Scene> activeScene; //DO NOT CHANGE THE ORDER OF THESE POINTERS, WILL BREAK INITIALIZATION
    std::shared_ptr<Scene> nextScene; //DO NOT CHANGE THE ORDER OF THESE POINTERS, WILL BREAK INITIALIZATION
    std::unique_ptr<GameMode> gameMode; //DO NOT CHANGE THE ORDER OF THESE POINTERS, WILL BREAK INITIALIZATION
    //DO NOT CHANGE THE ORDER OF THESE POINTERS, WILL BREAK INITIALIZATION
};


