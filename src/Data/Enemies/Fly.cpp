#include "Fly.h"
#include "../../Global.h"
#include "EnemyStateHandler.h"


Fly::Fly(Vector2 initialPos, EnemyLevel enemyLevel) : Enemy(EnemyTypes::Flyer)
{
	this->enemyLevel = enemyLevel;
	switch (enemyLevel)
	{
	case EnemyLevel::Low:
		texture = LoadTexture("assets/graphics/Enemies/Fliege_01_Spritesheet.png");
		health = 2;
		break;
	case EnemyLevel::Medium:
		texture = LoadTexture("assets/graphics/Enemies/Fliege_02_Spritesheet.png");
		health = 3;
		break;
	case EnemyLevel::High:
		texture = LoadTexture("assets/graphics/Enemies/Fliege_03_Spritesheet.png");
		health = 4;
		break;
	default:
		break;
	}
	

	position.x = initialPos.x;
	position.y = initialPos.y;

	activeState = std::make_shared<EnemyStateHandler>(*this);

	movementSpeed = 0.5f;
}

void Fly::Update()
{
	activeState = activeState->Update(*this);

	UpdateCollider(0, 20, 32, 12);

	if (invulnerable) {
		invulnerableCounter++;
		if (invulnerableCounter >= 45) {
			invulnerableCounter = 0;
			invulnerable = false;
		}
	}

	
	CollisionLeft(sceneManager->GetTilemap(), GetType());
	CollisionRight(sceneManager->GetTilemap(), GetType());
	CollisionGround(sceneManager->GetTilemap(), GetType());
	CollisionHead(sceneManager->GetTilemap(), GetType());
}

void Fly::Draw()
{
	activeState->Draw(*this);
	if constexpr (DEBUG_BUILD) DrawText(TextFormat("%i", health), position.x, position.y - 50, 30, WHITE);
}
