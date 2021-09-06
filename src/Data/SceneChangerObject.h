#pragma once
#include "raylib.h"
#include "../Core/Interactable.h"
#include "../Scenes/SceneEnums.h"

class SceneChangerObject : public Interactable {
public:
    SceneChangerObject(Vector2 location={0,0}, SceneEnums destination = SceneEnums::NeutralArea, SceneEnums start = SceneEnums::Default );
    void Interact(Actor& actor)override;
    void Update() override;
    void Draw() override;
    ~SceneChangerObject() override = default;
private:
    Vector2 position;
    SceneEnums chosenScene;
    SceneEnums comingFromThisScene;
    bool sceneIsChanging{ false };
    unsigned int fadeOutCounter = 0;
    bool fadeOutcomplete = false;
protected:
};
