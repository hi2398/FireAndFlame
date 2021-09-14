//
// Created by Ashty on 08.09.2021.
//

#include "NPC.h"

NPC::NPC(std::string dialogFilepath, Vector2 position, NPCType npcType,std::string gamepadDialogue) : DialogueObject(dialogFilepath, position, true) {
    type = npcType;
    switch (type) {
        case NPCType::one:
            drawBox = {0,0,32,32};
            break;
        case NPCType::two:
            drawBox = {96,0,32,32};
            break;
        case NPCType::three:
            drawBox = {192,0,32,32};
            break;
        case NPCType::four:
            drawBox = {96,32,32,32};
            break;
        case NPCType::five:
            drawBox = {192,32,32,32};
            break;
        default:
            break;
    }
    counter = GetRandomValue(10,20);
    this->position = position;
    objTexture = LoadTexture("assets/graphics/NPCs/NPCs.png");
    objFilepath = dialogFilepath;
    gamepadObjFilepath = gamepadDialogue;
}

void NPC::Update() {
    DialogueObject::Update();
    if(IsGamepadAvailable(0)){
        DialogueObject::SetDialoguePath(gamepadObjFilepath);
    }else {
        DialogueObject::SetDialoguePath(objFilepath);
    }

    --counter;
    if(counter <= 0){
        counter = 15;
        switch ((int)drawBox.x) {
            case 0: drawBox.x = 32;
                return;
            case 32: drawBox.x = 64;
                return;
            case 64: drawBox.x = 0;
                return;
            case 96: drawBox.x = 128;
                return;
            case 128: drawBox.x = 160;
                return;
            case 160: drawBox.x = 96;
                return;
            case 192: drawBox.x = 224;
                return;
            case 224: drawBox.x = 256;
                return;
            case 256: drawBox.x = 192;
                return;
        }
    }
    float playerReference = position.x - playerCharacter->GetPosition().x;
    if (playerReference >= 0) {
        drawBox.width = (float)-32;
    }
    else {
        drawBox.width = (float)32;
    }
    
}

void NPC::Draw() {
    DrawTextureRec(objTexture,drawBox,position,WHITE);
}

NPC::~NPC()
{
    UnloadTexture(objTexture);
}
