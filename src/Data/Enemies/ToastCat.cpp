#include "ToastCat.h"
#include "../../Global.h"
#include "EnemyStateHandler.h"


ToastCat::ToastCat(Vector2 initialPos) : Enemy(EnemyTypes::ToastCat)
{
	texture = LoadTexture("assets/graphics/Enemies/ToastCat_Spritesheet.png");
	position.x = initialPos.x;
	position.y = initialPos.y;

	activeState = std::make_shared<EnemyStateHandler>(*this);

}

void ToastCat::Update()
{
	activeState = activeState->Update(*this);

	UpdateCollider(0, 10, 32, 22);

	if (invulnerable) {
		invulnerableCounter++;
		if (invulnerableCounter >= 45) {
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

void ToastCat::Draw()
{
	activeState->Draw(*this);
	if constexpr (DEBUG_BUILD) DrawText(TextFormat("%i", health), position.x, position.y - 50, 30, WHITE);
}

ToastCat::~ToastCat()
{
	UnloadTexture(texture);
}

