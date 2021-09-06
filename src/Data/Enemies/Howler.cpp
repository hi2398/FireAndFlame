#include "Howler.h"
#include "../../Global.h"
#include "EnemyStateHandler.h"


Howler::Howler(Vector2 initialPos, EnemyLevel enemyLevel) : Enemy(EnemyTypes::Howler)
{
	this->enemyLevel = enemyLevel;
	switch (enemyLevel)
	{
	case EnemyLevel::Low:
		texture = LoadTexture("assets/graphics/Enemies/Doggo_01_Spritesheet.png");
		health = 5;
		break;
	case EnemyLevel::Medium:
		texture = LoadTexture("assets/graphics/Enemies/Doggo_02_Spritesheet.png");
		health = 7;
		break;
	default:
		break;
	}
	
	position.x = initialPos.x;
	position.y = initialPos.y;

	activeState = std::make_shared<EnemyStateHandler>(*this);

	jumpSpeed = 5.0f;
}

void Howler::Update()
{
	if (IsGrounded()) SetJumpCommand(false), SetJumpSpeed(5.0f), SetFallingSpeed(0.0f);
	activeState = activeState->Update(*this);

	UpdateAttackHitbox();
	UpdateCollider(0, 0, 32, 32);

	if (invulnerable) {
		invulnerableCounter++;
		if (invulnerableCounter >= 60) {
			invulnerableCounter = 0;
			invulnerable = false;
		}
	}

	if (!IsGrounded() && !GetJumpCommand()) {
		position.y += GetFallingSpeed();
		SetFallingSpeed(GetFallingSpeed() + 0.1f);
		if (GetFallingSpeed() >= 8.0f) {
			SetFallingSpeed(8.0f);
		}
	}
	CollisionLeft(sceneManager->GetTilemap(), GetType());
	CollisionRight(sceneManager->GetTilemap(), GetType());
	CollisionGround(sceneManager->GetTilemap(), GetType());
	CollisionHead(sceneManager->GetTilemap(), GetType());
}

void Howler::Draw()
{
	activeState->Draw(*this);
}