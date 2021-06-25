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
	
	PlayerCollisionLeft(tilemap);
	PlayerCollisionRight(tilemap);
	PlayerCollision(tilemap);
	if (playerCharacter->GetJumpCommand() || playerCharacter->IsGrounded())PlayerCollisionHead(tilemap);
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

void PlayerCollision(std::unique_ptr<Tilemap>& tilemap)
{
	//tile rectangles
	Rectangle tileRec = { 0,0,32,32 };

	//player vector alias
	const auto lastPos = playerCharacter->GetLastPosition();
	const auto newPos = playerCharacter->GetPosition();

	for (const auto& collTile : tilemap->GetTileColliders()) {
		tileRec.x = collTile.x;
		tileRec.y = collTile.y;
		
		//player coll ground
		Rectangle playerFeet = { newPos.x, newPos.y + 32, 32, 1 };

		if (CheckCollisionRecs(tileRec, playerFeet)) {
			playerCharacter->SetGrounded(true);
			playerCharacter->SetPosition({ newPos.x, tileRec.y - 32.0f });
			return;
		}
		else playerCharacter->SetGrounded(false);
	}
}

void PlayerCollisionLeft(std::unique_ptr<Tilemap>& tilemap) {
	//tile rectangles
	Rectangle tileRec = { 0,0,32,32 };

	//player vector alias
	const auto lastPos = playerCharacter->GetLastPosition();
	const auto newPos = playerCharacter->GetPosition();

	for (const auto& collTile : tilemap->GetTileColliders()) {
		tileRec.x = collTile.x;
		tileRec.y = collTile.y;

		//player coll left
		Rectangle playerLeftSide = { newPos.x - 1, newPos.y + 6, 1, 20 };

		if (CheckCollisionRecs(tileRec, playerLeftSide)) {
			std::cout << "LEFT COLL\n";
			playerCharacter->SetWallCollisionLeft(true);
			playerCharacter->SetPosition({ tileRec.x + 32, newPos.y });
			return;
		}
		else {
			playerCharacter->SetWallCollisionLeft(false);
		}
	}
}

void PlayerCollisionRight(std::unique_ptr<Tilemap>& tilemap) {
	//tile rectangles
	Rectangle tileRec = { 0,0,32,32 };

	//player vector alias
	const auto lastPos = playerCharacter->GetLastPosition();
	const auto newPos = playerCharacter->GetPosition();

	for (const auto& collTile : tilemap->GetTileColliders()) {
		tileRec.x = collTile.x;
		tileRec.y = collTile.y;

		//player coll right
		Rectangle playerRightSide = { newPos.x + 32, newPos.y + 6, 1, 20 };

		if (CheckCollisionRecs(tileRec, playerRightSide)) {
			std::cout << "RIGHT COLL\n";
			playerCharacter->SetWallCollisionRight(true);
			playerCharacter->SetPosition({ tileRec.x - 32, newPos.y });
			return;
		}
		else {
			playerCharacter->SetWallCollisionRight(false);
		}
	}
}

void PlayerCollisionHead(std::unique_ptr<Tilemap>& tilemap) {
	//tile rectangles
	Rectangle tileRec = { 0,0,32,32 };

	//player vector alias
	const auto lastPos = playerCharacter->GetLastPosition();
	const auto newPos = playerCharacter->GetPosition();

	for (const auto& collTile : tilemap->GetTileColliders()) {
		tileRec.x = collTile.x;
		tileRec.y = collTile.y;

		//player coll head
		Rectangle playerUpperSide = { newPos.x , newPos.y - 1, 32, 1 };

		if (CheckCollisionRecs(tileRec, playerUpperSide)) {
			std::cout << "HEAD COLL\n";
			playerCharacter->SetHeadCollision(true);
			playerCharacter->SetJumpCommand(false);
			playerCharacter->SetPosition({ newPos.x, tileRec.y + 32 });
			return;
		}
		else {
			playerCharacter->SetHeadCollision(false);
		}
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

	DrawText(TextFormat("%i", playerCharacter->GetHeadCollision()), playerCharacter->GetPosition().x, playerCharacter->GetPosition().y-100, 30, WHITE);
}
