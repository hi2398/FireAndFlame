#pragma once
#include "DialogueManager.h"
#include <memory>
#include <list>
#include "Tilemap.h"
#include "Enemy.h"
#include "Interactable.h"

class Scene {
public:
    explicit Scene(std::string filepath);
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual ~Scene() = default;

    [[nodiscard]] DialogueManager &GetDialogueManager();
    [[nodiscard]] const std::unique_ptr<Tilemap>& GetTilemap();

    [[nodiscard]] const std::list<std::unique_ptr<Interactable>> &GetInteractables() const;
    [[nodiscard]] const std::list<std::unique_ptr<Enemy>> &GetEnemies() const;

    void RemoveMarkedDelete();

protected:
    DialogueManager dialogueMananger;
    std::unique_ptr<Tilemap> tilemap;
    std::list<std::unique_ptr<Interactable>> interactables;
    std::list<std::unique_ptr<Enemy>> enemies;
private:

};


