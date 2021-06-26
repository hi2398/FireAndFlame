
#include "Scene.h"

Scene::Scene(std::string filepath) : dialogueMananger(filepath) {

}

DialogueMananger &Scene::GetDialogueManager() {
    return dialogueMananger;
}


