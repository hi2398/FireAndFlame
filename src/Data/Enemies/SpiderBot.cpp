#include "SpiderBot.h"
#include "../../Global.h"
#include "EnemyStateHandler.h"


SpiderBot::SpiderBot(Vector2 initialPos) : Enemy(EnemyTypes::SpiderBot)
{
	texture = LoadTexture("assets/graphics/Enemies/SpiderBot_01_Spritesheet.png");

	position.x = initialPos.x;
	position.y = initialPos.y;

	activeState = std::make_shared<EnemyStateHandler>(*this);

	movementSpeed = 1.0f;
}

void SpiderBot::Update()
{
	activeState = activeState->Update(*this);

	UpdateCollider(0, 0, 32, 32);

	if (invulnerable) {
		invulnerableCounter++;
		if (invulnerableCounter >= 60) {
			invulnerableCounter = 0;
			invulnerable = false;
		}
	}
	CheckEdgeColl();
	if (!IsGrounded() && !GetWallCollisionLeft() && !GetWallCollisionRight() && !GetHeadCollision()) position.y += 2.0f;


	CollisionLeft(sceneManager->GetTilemap());
	CollisionRight(sceneManager->GetTilemap());
	CollisionGround(sceneManager->GetTilemap());
	CollisionHead(sceneManager->GetTilemap());

	
}

void SpiderBot::Draw()
{
	activeState->Draw(*this);
	DrawText(TextFormat("%i", health), position.x, position.y - 50, 30, WHITE);
}

void SpiderBot::CheckEdgeColl() {
	//check for ledges
	Rectangle edgeSeekerLeft = { position.x - 2, position.y + 32, 1, 1 };
	Rectangle edgeSeekerRight = {position.x + 32 + 1, position.y + 32, 1, 1 };
	Rectangle edgeSeekerUpLeft = {position.x - 2, position.y - 2, 1, 1};
	Rectangle edgeSeekerUpRight = { position.x + 32, position.y - 2, 1, 1 };
	Rectangle tileRec = { 0,0,32,32 };
	for (const auto& collTile : sceneManager->GetTilemap()->GetTileColliders())
	{
		tileRec.x = collTile.x;
		tileRec.y = collTile.y;

		if (!IsGrounded() && !GetWallCollisionLeft() && !GetWallCollisionRight() && !GetHeadCollision()) {
			if ((CheckCollisionRecs(tileRec, edgeSeekerLeft) && GetDirection() == LEFT) || (CheckCollisionRecs(tileRec, edgeSeekerRight) && GetDirection() == RIGHT)) {
				position.y -= 10.0f;
				position.x += 10.0f * GetDirection();
			}
			if ((CheckCollisionRecs(tileRec, edgeSeekerUpLeft) && GetDirection() == RIGHT) || (CheckCollisionRecs(tileRec, edgeSeekerUpRight) && GetDirection() == LEFT)) {
				position.x -= 10.0f * GetDirection();
			}
			if ((CheckCollisionRecs(tileRec, edgeSeekerUpLeft) && GetDirection() == LEFT) || (CheckCollisionRecs(tileRec, edgeSeekerUpRight) && GetDirection() == RIGHT)) {
				position.y -= 10.0f;
			}
		}
	}
}
