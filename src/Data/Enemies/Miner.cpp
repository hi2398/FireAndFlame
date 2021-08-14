#include "Miner.h"
#include "../../Global.h"
#include "EnemyStateHandler.h"

Miner::Miner(Vector2 initialPos, EnemyLevel enemyLevel): Enemy(EnemyTypes::Miner)
{
	this->enemyLevel = enemyLevel;
	switch (enemyLevel)
	{
	case EnemyLevel::Low:
		texture = LoadTexture("assets/graphics/Enemies/Miner_01_Spritesheet.png");
		health = 3;
		break;
	case EnemyLevel::Medium:
		texture = LoadTexture("assets/graphics/Enemies/Miner_02_Spritesheet.png");
		health = 5;
		break;
	case EnemyLevel::High:
		texture = LoadTexture("assets/graphics/Enemies/Miner_03_Spritesheet.png");
		health = 10;
		break;
	default:
		break;
	}
	
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
	CollisionLeft(sceneManager->GetTilemap(), GetType());
	CollisionRight(sceneManager->GetTilemap(), GetType());
	CollisionGround(sceneManager->GetTilemap(), GetType());
	CollisionHead(sceneManager->GetTilemap(), GetType());
}

void Miner::Draw()
{
	activeState->Draw(*this);
	if constexpr (DEBUG_BUILD)  DrawText(TextFormat("%i", health), position.x, position.y-50, 30, WHITE);
}
