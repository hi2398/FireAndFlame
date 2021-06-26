
#include "Scene.h"

Scene::Scene(std::string filepath) : dialogueMananger(filepath) {

}

DialogueMananger &Scene::GetDialogueManager() {
    return dialogueMananger;
}



const std::unique_ptr<Tilemap>& Scene::GetTilemap()
{
    return tilemap;
}
