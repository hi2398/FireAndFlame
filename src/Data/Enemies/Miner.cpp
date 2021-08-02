#include "Miner.h"
#include "../../Global.h"
#include "EnemyStateHandler.h"

Miner::Miner(Vector2 initialPos): Enemy(EnemyTypes::Miner)
{
	texture = LoadTexture("assets/graphics/Enemies/Miner_01_Spritesheet.png");
	position.x = initialPos.x;
	position.y = initialPos.y;
	hitbox.x = initialPos.x;
	hitbox.y = initialPos.y;
	hitbox.width = 32;
	hitbox.height = 32;
	movementSpeed = 1.0f;
	activeState = std::make_shared<EnemyStateHandler>(*this);
}

void Miner::Update() {
	activeState = activeState->Update(*this);

	UpdateAttackHitbox();
	UpdateCollider(0, 15, 32, 17);

	if (invulnerable) {
		invulnerableCounter++;
		if (invulnerableCounter >= 60) {
			invulnerableCounter = 0;
			invulnerable = false;
		}
	}

	if (!IsGrounded()) position.y += 2.0f;
	CollisionLeft(sceneManager->GetTilemap());
	CollisionRight(sceneManager->GetTilemap());
	CollisionGround(sceneManager->GetTilemap());
	CollisionHead(sceneManager->GetTilemap());
}

void Miner::Draw()
{
	activeState->Draw(*this);
	DrawText(TextFormat("%i", health), position.x, position.y-50, 30, WHITE);
}
