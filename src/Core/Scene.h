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
    void UpdateScreenShake();
    virtual void Draw();
    void DrawBackground() const;
    virtual ~Scene() = default;

    [[nodiscard]] DialogueManager &GetDialogueManager();
    [[nodiscard]] const std::unique_ptr<Tilemap>& GetTilemap();

    [[nodiscard]] const std::list<std::unique_ptr<Interactable>> &GetInteractables() const;
    [[nodiscard]] const std::list<std::unique_ptr<Enemy>> &GetEnemies() const;

    void AddEnemy(std::unique_ptr<Enemy> enemy);
    void AddInteractable(std::unique_ptr<Interactable> interactable);

    void RemoveMarkedDelete();
    void RemoveInteractables();

    void ActivateScreenShake(int durationInSeconds);

protected:
    DialogueManager dialogueMananger;
    std::unique_ptr<Tilemap> tilemap;
    std::list<std::unique_ptr<Interactable>> interactables;
    std::list<std::unique_ptr<Enemy>> enemies;

    Texture2D textureForegroundBottom;
    Texture2D textureForegroundSide;
    Texture2D textureBackground;
    Texture2D textureUpperBackground;

    int skipFrame = 0;

    Vector2 tmp1 = {};
    Vector2 tmp2 = {};

    Vector2 foregroundPos{};
    Vector2 backgroundPos{};

    int foregroundException{};
    int backgroundException{};

    int backgroundLoopX = 0;
    int backgroundLoopY = 0;
    int foregroundLoopX = 0;
    int foregroundLoopY = 0;

    bool screenShakeActivated{ false };
    int duration = -1;
    int shakeFrameCounter = 0;
    float xOffset = 0.0;

private:
};


