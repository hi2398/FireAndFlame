#include "Saugi.h"
#include "../../Global.h"
#include "EnemyStateHandler.h"


Saugi::Saugi(Vector2 initialPos) : Enemy(EnemyTypes::Saugi)
{
	texture = LoadTexture("assets/graphics/Enemies/Saugi_Spritesheet.png");

	position.x = initialPos.x;
	position.y = initialPos.y;

	activeState = std::make_shared<EnemyStateHandler>(*this);

	movementSpeed = 0.5f;
}

void Saugi::Update()
{
	activeState = activeState->Update(*this);

	UpdateCollider(6, 20, 20, 12);

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

void Saugi::Draw()
{
	activeState->Draw(*this);
	if constexpr (DEBUG_BUILD)  DrawText(TextFormat("%i", health), position.x, position.y - 50, 30, WHITE);
}

Saugi::~Saugi() {
	UnloadTexture(texture);
}