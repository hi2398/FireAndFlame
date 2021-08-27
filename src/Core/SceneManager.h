#pragma once
#include <memory>
#include "../Data/Player/PlayerCharacter.h"
#include "PlayerController.h"
#include "../Data/HUD.h"
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

    void AddEnemy(std::unique_ptr<Enemy> enemy);
    void AddInteractable(std::unique_ptr<Interactable> interactable);
    void RemoveAllInteractables();

    void SaveGame(std::string saveFolder, int slot);
    void LoadGame(std::string saveFolder, int slot);

    void ScreenShake(int durationInSeconds);

    [[nodiscard]] std::shared_ptr<Scene> GetActiveScene();

protected:

private:
    Vector2 virtualMousePosition;
    std::shared_ptr<Scene> activeScene;
    std::shared_ptr<Scene> nextScene;


};


