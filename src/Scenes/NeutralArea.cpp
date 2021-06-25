#include "NeutralArea.h"
#include "raylib.h"
#include "../Global.h"


NeutralArea::NeutralArea() {
	tilemap = std::make_unique<Tilemap>("assets/Tilemaps/Testmap/Placehalter_2.json", "assets/Tilemaps/Testmap/NEUTRAL_AREA.json");
}

void NeutralArea::Update() {
	//decrease player health every second
	generalTimer++;
	if (generalTimer >= 30) {
		generalTimer = 0;
		playerCharacter->SetHealth(playerCharacter->GetHealth() - 1);
	}

	PlayerGroundCollision(tilemap);

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

void PlayerGroundCollision(std::unique_ptr<Tilemap>& tilemap)
{
	Vector2 collisionPoint1;
	Vector2 collisionPoint2;
	Rectangle tileRec = { 0,0,32,32 };
	for (const auto& collTile : tilemap->GetTileColliders()) {
		tileRec.x = collTile.x;
		tileRec.y = collTile.y;
		const auto lastPos = playerCharacter->GetLastPosition();
		const auto newPos = playerCharacter->GetPosition();
		Rectangle playerFeet = { newPos.x, newPos.y + 32, 32, 1 };
		
		if (CheckCollisionRecs(tileRec, playerFeet)) {
			playerCharacter->SetGrounded(true);
			playerCharacter->SetPosition({ newPos.x, tileRec.y - 32.0f });
			return;
		}
		else playerCharacter->SetGrounded(false);
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

	const auto lastPos = playerCharacter->GetLastPosition();
	const auto newPos = playerCharacter->GetPosition();
	DrawLineV({ lastPos.x, lastPos.y + 32.0f },
		{ newPos.x, newPos.y + 32.0f }, GREEN);
	DrawLineV({ lastPos.x + 32.0f, lastPos.y + 32.0f },
		{ newPos.x + 32.0f, newPos.y + 32.0f }, GREEN);

	//DrawText(TextFormat(" % f", playerCharacter->GetLastPosition().x), playerCharacter->GetPosition().x, playerCharacter->GetPosition().y-150, 30, WHITE);
	DrawText(TextFormat(" % f", playerCharacter->GetPosition().y), playerCharacter->GetPosition().x, playerCharacter->GetPosition().y - 100, 30, WHITE);
}
