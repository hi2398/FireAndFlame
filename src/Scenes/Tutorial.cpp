#include "Tutorial.h"
#include "../Global.h"
#include "../Data/DialogueObject.h"

Tutorial::Tutorial() {
    playerCharacter->SetPosition(playerStart);
    playerCharacter->active = true;
    npcTex = LoadTexture("assets/graphics/PLAYER.png"); // TODO change NPC Texture
    tilemap=std::make_unique<Tilemap>("assets/Tilemaps/Testmap/Placehalter_2.json","assets/Tilemaps/Testmap/Tutorial.json");
    interactables.emplace_back(std::make_unique<DialogueObject>("assets/Dialogues/tutorialText1.json",npc1Pos,npcTex));
}

void Tutorial::Update() {

}

void Tutorial::Draw() {

}
