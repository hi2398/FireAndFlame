//
// Created by Ashty on 06.06.2021.
//

#include "TestScene.h"
#include "../Core/Tilemap.cpp"
#include "raylib.h"
#include <iostream>

TestScene::TestScene() {
    tilemap=std::make_unique<Tilemap>("assets/Tilemaps/Testmap/Placehalter_2.json","assets/Tilemaps/Testmap/Map_2.json");
}

void TestScene::Update() {
    Rectangle tempVec = {0,0,32,32};
    for(const auto& x: tilemap->GetWorldPos()){
        tempVec.x = x.x;
        tempVec.y = x.y;
        if(CheckCollisionRecs(tempVec, playerCharacter->playerHitbox)) {
            playerCharacter->isGrounded = true;
            std::cout << "Scene " << playerCharacter->isGrounded << "\n";
            break;
        }else {
            playerCharacter->isGrounded = false;
            std::cout << "Scene2 " << playerCharacter->isGrounded << "\n";
        }
    }
}

void TestScene::Draw() {
    tilemap->Draw();
}