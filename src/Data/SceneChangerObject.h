#pragma once
#include "raylib.h"
#include "../Core/Interactable.h"
#include "../Scenes/NeutralArea.h"
#include "../Scenes/AreaOne.h"

class SceneChangerObject : public Interactable {
public:
    SceneChangerObject(Vector2 location={0,0});
    void Interact(Actor& actor)override;
    void Update() override;
    void Draw() override;
    ~SceneChangerObject() override = default;
private:
    Vector2 position;
protected:
};
