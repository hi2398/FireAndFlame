#include "Howler.h"
#include "../../Global.h"
#include "EnemyStateHandler.h"


Howler::Howler(Vector2 initialPos) : Enemy(EnemyTypes::Howler)
{
	texture = LoadTexture("assets/graphics/Enemies/Doggo_01_Spritesheet.png");
	
	position.x = initialPos.x;
	position.y = initialPos.y;

	activeState = std::make_shared<EnemyStateHandler>(*this);

	jumpSpeed = 5.0f;

	health = 10;
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
	CollisionLeft(sceneManager->GetTilemap());
	CollisionRight(sceneManager->GetTilemap());
	CollisionGround(sceneManager->GetTilemap());
	CollisionHead(sceneManager->GetTilemap());
}

void Howler::Draw()
{
	activeState->Draw(*this);
}