#include "Howler.h"
#include "../../Global.h"
#include "EnemyStateHandler.h"


Howler::Howler(Vector2 initialPos) : Enemy(EnemyTypes::Howler)
{
	texture = LoadTexture("assets/graphics/Enemies/ToastCat.png");
	
	position.x = initialPos.x;
	position.y = initialPos.y;

	activeState = std::make_shared<EnemyStateHandler>(*this);

	
}

void Howler::Update()
{
	activeState = activeState->Update(*this);

	UpdateAttackHitbox();
	UpdateCollider();

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

void Howler::Draw()
{
	activeState->Draw(*this);
}