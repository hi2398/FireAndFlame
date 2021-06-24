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

	Vector2 collisionPoint1;
	Vector2 collisionPoint2;
	Rectangle tileRec = { 0,0,32,32 };
	for (const auto& collTile : tilemap->GetTileColliders()) {
		const auto lastPos = playerCharacter->GetLastPosition();
		const auto newPos = playerCharacter->GetPosition();
		//left edge
		if (CheckCollisionLines(
			{ lastPos.x, lastPos.y + 32.0f },
			{ newPos.x, newPos.y + 32.0f },
			{ collTile.x, collTile.y },
			{ collTile.x + 32.0f, collTile.y },
			&collisionPoint1)) 
		{
			std::cout << "coll\n";
			playerCharacter->SetGrounded(true);
			playerCharacter->SetPosition({ newPos.x, collisionPoint1.y - 33.0f });
			break;
		}
		else {
			playerCharacter->SetGrounded(false);
		}

		//right edge
		if (CheckCollisionLines(
		{ lastPos.x + 32.0f, lastPos.y + 32.0f },
		{ newPos.x + 32.0f, newPos.y + 32.0f },
		{ collTile.x, collTile.y },
		{ collTile.x + 32.0f, collTile.y },
		&collisionPoint2))
		{
			std::cout << "coll\n";
			playerCharacter->SetPosition({ newPos.x, collisionPoint2.y - 33.0f });
			playerCharacter->SetGrounded(true);
			break;
		}
		else {
			playerCharacter->SetGrounded(false);
		}
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

	const auto lastPos = playerCharacter->GetLastPosition();
	const auto newPos = playerCharacter->GetPosition();
	DrawLineV({ lastPos.x, lastPos.y + 32.0f },
		{ newPos.x, newPos.y + 32.0f }, GREEN);
	DrawLineV({ lastPos.x + 32.0f, lastPos.y + 32.0f },
		{ newPos.x + 32.0f, newPos.y + 32.0f }, GREEN);

	DrawText(TextFormat(" % i", playerCharacter->IsGrounded()), playerCharacter->GetPosition().x, playerCharacter->GetPosition().y-100, 30, WHITE);
}
