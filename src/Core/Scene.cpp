
#include "Scene.h"
#include "raymath.h"
#include "../Global.h"
#include <utility>

DialogueManager &Scene::GetDialogueManager() {
    return dialogueMananger;
}



const std::unique_ptr<Tilemap>& Scene::GetTilemap() {
    return tilemap;
}

const std::list<std::unique_ptr<Interactable>> &Scene::GetInteractables() const {
    return interactables;
}

const std::list<std::unique_ptr<Enemy>> &Scene::GetEnemies() const {
    return enemies;
}



void Scene::RemoveMarkedDelete() {

    //remove enemies marked delete
    auto enemyIterator= enemies.begin();
    while (enemyIterator!=enemies.end()) {
        if ((*enemyIterator)->IsMarkedDestroy()) {
            enemies.erase(enemyIterator++);
        }else ++enemyIterator;
    }

    //remove interactables marked delete
    auto interactableIterator= interactables.begin();
    while (interactableIterator!=interactables.end()) {
        if ((*interactableIterator)->IsMarkedDestroy()) {
            interactables.erase(interactableIterator++);
        } else ++interactableIterator;
    }

}

void Scene::Update() {
    if (skipFrame > 0) {
        tmp1 = playerCharacter->GetLastPosition();
        tmp2 = playerCharacter->GetPosition();
        Vector2 scrollDirection = { tmp2.x - tmp1.x, tmp2.y - tmp1.y };

        foregroundPosition = Vector2Add(foregroundPosition, Vector2Multiply(scrollDirection, { 0.3f, 0.1f }));
        middlegroundPosition = Vector2Add(middlegroundPosition, Vector2Multiply(scrollDirection, { 0.2f, 0.05f }));
        backgroundPosition = Vector2Add(backgroundPosition, Vector2Multiply(scrollDirection, { 0.1f, 0.0f }));
    }


    skipFrame++;
}

void Scene::Draw() {
}

void Scene::DrawBackground() const {
    DrawTextureEx(textureBackground, backgroundPosition, 0, 1.0f, WHITE);
    DrawTextureEx(textureMiddleground, middlegroundPosition, 0, 1.0f, WHITE);
    DrawTextureEx(textureForeground, foregroundPosition, 0, 1.0f, WHITE);
}

void Scene::AddEnemy(std::unique_ptr<Enemy> enemy) {
    enemies.emplace_back(std::move(enemy));
}

void Scene::AddInteractable(std::unique_ptr<Interactable> interactable) {
    interactables.emplace_back(std::move(interactable));
}

void Scene::RemoveInteractables() { //TODO Make it work pls :D
    for (const auto& interactable : interactables) {
        interactable->MarkToDestroy();
    }
}
