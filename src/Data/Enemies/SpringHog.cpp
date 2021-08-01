#include "SpringHog.h"
#include "../../Global.h"
#include "EnemyStateHandler.h"


SpringHog::SpringHog(Vector2 initialPos) : Enemy(EnemyTypes::SpringHog)
{
	texture = LoadTexture("assets/graphics/Enemies/Hogbot_Spritesheet.png");

	position.x = initialPos.x;
	position.y = initialPos.y;

	activeState = std::make_shared<EnemyStateHandler>(*this);

	movementSpeed = 3.0f;
}

void SpringHog::Update()
{
	activeState = activeState->Update(*this);

	UpdateCollider();

	if (invulnerable) {
		invulnerableCounter++;
		if (invulnerableCounter >= 60) {
			invulnerableCounter = 0;
			invulnerable = false;
		}
	}
	if (!IsGrounded() && !GetJumpCommand()) position.y += 2.0f;


	CollisionLeft(sceneManager->GetTilemap());
	CollisionRight(sceneManager->GetTilemap());
	CollisionGround(sceneManager->GetTilemap());
	CollisionHead(sceneManager->GetTilemap());


}

void SpringHog::Draw()
{
	activeState->Draw(*this);
	DrawText(TextFormat("%i", health), position.x, position.y - 50, 30, WHITE);
}