
#include "Scene.h"

#include <utility>

Scene::Scene(std::string filepath) : dialogueMananger(std::move(filepath)) {

}

DialogueManager &Scene::GetDialogueManager() {
    return dialogueMananger;
}



const std::unique_ptr<Tilemap>& Scene::GetTilemap() {
    return tilemap;
}

const std::vector<std::unique_ptr<Interactable>> &Scene::GetInteractables() const {
    return interactables;
}

const std::vector<std::unique_ptr<Enemy>> &Scene::GetEnemies() const {
    return enemies;
}
