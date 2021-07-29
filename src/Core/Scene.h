#pragma once
#include "DialogueManager.h"
#include <memory>
#include <list>
#include "Tilemap.h"
#include "Enemy.h"
#include "Interactable.h"


class Scene {
public:
    virtual void Update();
    virtual void Draw();
    virtual ~Scene() = default;

    [[nodiscard]] DialogueManager &GetDialogueManager();
    [[nodiscard]] const std::unique_ptr<Tilemap>& GetTilemap();

    [[nodiscard]] const std::list<std::unique_ptr<Interactable>> &GetInteractables() const;
    [[nodiscard]] const std::list<std::unique_ptr<Enemy>> &GetEnemies() const;

    void AddEnemy(std::unique_ptr<Enemy> enemy);
    void AddInteractable(std::unique_ptr<Interactable> interactable);

    void RemoveMarkedDelete();
    void RemoveInteractables();

protected:
    DialogueManager dialogueMananger;
    std::unique_ptr<Tilemap> tilemap;
    std::list<std::unique_ptr<Interactable>> interactables;
    std::list<std::unique_ptr<Enemy>> enemies;

    Texture2D textureForeground;
    Texture2D textureMiddleground;
    Texture2D textureBackground;

    int skipFrame = 0;

    Vector2 tmp1 = {};
    Vector2 tmp2 = {};

    Vector2 foregroundPosition{};
    Vector2 middlegroundPosition{};
    Vector2 backgroundPosition{};
private:

};


