#pragma once
#include "DialogueMananger.h"
#include <memory>
#include "Tilemap.h"

class Scene {
public:
    Scene(std::string filepath);
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual ~Scene() = default;
    DialogueMananger &GetDialogueManager();

    const std::unique_ptr<Tilemap>& GetTilemap();
protected:
    DialogueMananger dialogueMananger;
    std::unique_ptr<Tilemap> tilemap;
private:

};


