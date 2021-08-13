
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

        foregroundBottomPosition = Vector2Add(foregroundBottomPosition, Vector2Multiply(scrollDirection, { 0.6f, 0.2f }));
        foregroundSidePosition = Vector2Add(foregroundSidePosition, Vector2Multiply(scrollDirection, { 0.6f, 0.2f }));
        backgroundPosition = Vector2Add(backgroundPosition, Vector2Multiply(scrollDirection, { 1.0f, 0.9f }));
    }


    skipFrame++;
}

void Scene::Draw() {
}

void Scene::DrawBackground() const {
    //loop Background
    for (int y = 0; y < backgroundLoopY; y++) {
        for (int x = 0; x < backgroundLoopX; x++) {
            DrawTextureEx(textureBackground, { (float)backgroundPosition.x + x * textureBackground.width/2, (float)backgroundPosition.y + y * textureBackground.height/2 }, 0.0, 0.5, WHITE);
        }
    }

    //loop foreground
    for (int y = 0; y < foregroundLoopY; y++) {
        for (int x = 0; x < foregroundLoopX; x++) {
            if (y == foregroundLoopY - 1) {
                DrawTextureEx(textureForegroundBottom, { (float)foregroundBottomPosition.x + x * textureForegroundBottom.width, (float)foregroundBottomPosition.y + y * textureForegroundBottom.height }, 0.0, 1.0, WHITE);
            }
            else DrawTextureEx(textureForegroundSide, { (float)foregroundSidePosition.x + x * textureForegroundSide.width, (float)foregroundSidePosition.y + y * textureForegroundSide.height }, 0.0, 1.0, WHITE);
        }
    }

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
