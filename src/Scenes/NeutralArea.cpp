#include "NeutralArea.h"
#include "raylib.h"
#include "../Global.h"



NeutralArea::NeutralArea() : Scene("assets/Dialogues/testText.json") {
    tilemap=std::make_unique<Tilemap>("assets/Tilemaps/Testmap/Placehalter_2.json","assets/Tilemaps/Testmap/Map_2.json");
}

void NeutralArea::Update() {
	//decrease player health every second
	generalTimer++;
	if (generalTimer >= 30) {
		generalTimer = 0;
		playerCharacter->SetHealth(playerCharacter->GetHealth() - 1);
	}

	//coal X player && coal X ground collision
	if (coals->GetEnabled())
	{
		coals->Update();
		if (CheckCollisionRecs(ground, coals->GetHitbox()))
		{
			coals->SetGrounded(true);
		}
		else
		{
			coals->SetGrounded(false);
		}
		if (CheckCollisionRecs(playerCharacter->playerHitbox, coals->GetHitbox()))
		{
			coals->Interact();
		}

	}
	else
	{
		if (coalTimer == 0) {
			Vector2 pStartVectorCoal;
			pStartVectorCoal.x = 100;
			pStartVectorCoal.y = -50;
			coals->SetPosition(pStartVectorCoal);
			coals->SetEnabled(true);
			coalTimer = 60;
		}
		else
		{
			coalTimer--;
		}
	}
	for (const auto& x : enemies) {
		x->Update();
	}
}

void NeutralArea::Draw() {

	for (const auto& x : enemies) {
		x->Draw();
	}

	coals->Draw();

	tilemap->Draw();

	if constexpr (DEBUG_BUILD) {
		for (const auto x : tilemap->GetTileColliders()) {
			DrawRectangleLines(x.x, x.y, 32, 32, RED);
		}
	}

	DrawText(TextFormat("%i", playerCharacter->GetCanDoubleJump()), playerCharacter->GetPosition().x, playerCharacter->GetPosition().y-100, 30, WHITE);
}
