#include "SpringHog.h"
#include "../../Global.h"
#include "EnemyStateHandler.h"


SpringHog::SpringHog(Vector2 initialPos, EnemyLevel enemyLevel) : Enemy(EnemyTypes::SpringHog)
{
	this->enemyLevel = enemyLevel;
	switch (enemyLevel)
	{
	case EnemyLevel::Low:
		texture = LoadTexture("assets/graphics/Enemies/Hogbot_Spritesheet.png");
		health = 3;
		break;
	case EnemyLevel::Medium:
		texture = LoadTexture("assets/graphics/Enemies/Hogbot_02_Spritesheet.png");
		health = 10;
		break;
	default:
		break;
	}

	position.x = initialPos.x;
	position.y = initialPos.y;

	activeState = std::make_shared<EnemyStateHandler>(*this);

	movementSpeed = 3.0f;
	jumpSpeed = 3.0f;
}

void SpringHog::Update()
{
	activeState = activeState->Update(*this);

	UpdateCollider(8,0, 16, 32);

	if (invulnerable) {
		invulnerableCounter++;
		if (invulnerableCounter >= 60) {
			invulnerableCounter = 0;
			invulnerable = false;
		}
	}
	


	CollisionLeft(sceneManager->GetTilemap(), GetType());
	CollisionRight(sceneManager->GetTilemap(), GetType());
	CollisionGround(sceneManager->GetTilemap(), GetType());
	CollisionHead(sceneManager->GetTilemap(), GetType());

	if (IsGrounded()) SetJumpCommand(false), SetJumpSpeed(3.0f);
	if (GetHeadCollision()) SetJumpSpeed(0.0f);
	if (!IsGrounded() && !GetJumpCommand()) position.y += 2.0f;
}

void SpringHog::Draw()
{
	activeState->Draw(*this);
	if constexpr (DEBUG_BUILD)  DrawText(TextFormat("%i", health), position.x, position.y - 50, 30, WHITE);
}