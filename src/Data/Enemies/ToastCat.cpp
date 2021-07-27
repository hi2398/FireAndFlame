#include "ToastCat.h"
#include "../../Global.h"
#include "EnemyStateHandler.h"


ToastCat::ToastCat(Vector2 initialPos) : Enemy(EnemyTypes::ToastCat)
{
    texture = LoadTexture("assets/graphics/Enemies/ToastCat.png");
    toastTexture = LoadTexture("assets/graphics/Enemies/Toast.png");
	position.x = initialPos.x;
	position.y = initialPos.y;

	activeState = std::make_shared<EnemyStateHandler>(*this);
}

void ToastCat::Update()
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

void ToastCat::Draw()
{
	activeState->Draw(*this);
	DrawText(TextFormat("%i", health), position.x, position.y - 50, 30, WHITE);
}

