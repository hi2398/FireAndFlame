#pragma once
#include "DialogueManager.h"
#include "../Scenes/SceneEnums.h"
#include <memory>
#include <list>
#include "Tilemap.h"
#include "Enemy.h"
#include "Interactable.h"


class Scene {
public:
    Scene(SceneEnums sceneType);
    virtual void Update();
    void UpdateBackground();
    void UpdateSceneEffect();
    void UpdateScreenShake();
    virtual void Draw();
    void DrawBackground() const;
    void DrawForeground() const;
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

    SceneEnums GetSceneName() const;

protected:
    SceneEnums sceneName{SceneEnums::Default};
    SceneEnums lastScene{SceneEnums::Default};
    DialogueManager dialogueMananger;
    std::unique_ptr<Tilemap> tilemap;
    std::list<std::unique_ptr<Interactable>> interactables;
    std::list<std::unique_ptr<Enemy>> enemies;

    //background
    Texture2D textureForegroundException;
    Texture2D textureForegroundMain;
    Texture2D textureBackgroundMain;
    Texture2D textureBackgroundException;

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

    float backgroundMultiplier = 0.5f;

    //foreground, i.e. weather effects
    Texture2D sceneEffect;
    Vector2 effectPos1{};
    Vector2 effectPos2{};
    Vector2 effectPos1Start{};
    Vector2 effectPos2Start{};
    Vector2 effectDirection{-5.0f, 3.0f};
    bool sceneEffectActivated{ false };


    //screen shake variables
    bool screenShakeActivated{ false };
    int duration = -1;
    int shakeFrameCounter = 0;
    float xOffset = 0.0;

private:
};


