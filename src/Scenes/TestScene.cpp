//
// Created by Ashty on 06.06.2021.
//

#include "TestScene.h"
#include "../Core/Tilemap.cpp"

TestScene::TestScene() {
    tilemap=std::make_unique<Tilemap>("assets/Tilemaps/Testmap/Placehalter_2.json","assets/Tilemaps/Testmap/Map_2.json");
}

void TestScene::Update() {
}

void TestScene::Draw() {
    tilemap->Draw();
}
