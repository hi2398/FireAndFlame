#pragma once
#include <memory>
#include "../Data/Player/PlayerCharacter.h"
#include "PlayerController.h"
#include "../Data/HUD.h"
#include "BackgroundManager.h"
#include "Tilemap.h"
#include "Scene.h"


extern std::shared_ptr<PlayerCharacter> playerCharacter;
extern std::shared_ptr<PlayerController> playerController;
extern std::shared_ptr<HUD> hud;


class SceneManager {
public:
    explicit SceneManager(std::shared_ptr<Scene> initialScene);
    void Update(Vector2 virtualMousePosition);
    void Draw();
    void SetNextScene(std::unique_ptr<Scene> nextScene);
    void UpdateDialogInScene(std::string filepath);
    Vector2 GetVirtualMousePosition();

    [[nodiscard]] const std::list<std::unique_ptr<Interactable>> &GetInteractables() const;
    [[nodiscard]] const std::list<std::unique_ptr<Enemy>> &GetEnemies() const;
    [[nodiscard]] const std::unique_ptr<Tilemap>& GetTilemap();

    void SaveGame(std::string saveFolder, int slot);
    void LoadGame(std::string saveFolder, int slot);

protected:

private:
    Vector2 virtualMousePosition;
    std::shared_ptr<Scene> activeScene;
    std::shared_ptr<Scene> nextScene;
    std::shared_ptr<BackgroundManager> background = std::make_shared<BackgroundManager>();
};


