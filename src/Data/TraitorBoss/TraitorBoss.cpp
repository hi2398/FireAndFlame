#include "../../Global.h"

#include "TraitorBoss.h"
#include "TBBeforeFightState.h"
#include "TBIdleState.h"
#include "../../Scenes/TraitorBossScene.h"


TraitorBoss::TraitorBoss(Vector2 location) : Enemy(EnemyTypes::Boss)
{
	canUseCoal = true;
	health = MAX_HEALTH;
	movementSpeed = 3.0f;
	SetPosition(location);

	activeState = std::make_shared<TBIdleState>(*this);
	texture = LoadTexture("assets/Bosses/TraitorBoss/TraitorUpperBody.png");
	texture2 = LoadTexture("assets/Bosses/TraitorBoss/TraitorLegs.png");
	texture3 = LoadTexture("assets/Bosses/TraitorBoss/AttackSprites.png");
}

void TraitorBoss::Update()
{
	activeState = activeState->Update(*this);

	if (actionCounter == 2) cooldown--;
	if (cooldown == 0) actionCounter = 0;
	hud->SetBossEnemyHealth(health);
	if (health < MAX_HEALTH) isFighting = true;
	if (isFighting) {
		//decrease enemy health
		if (health > 0) {
			healthtimer++;
			if (healthtimer >= HEALTH_INTERVAL) {
				health--;
				healthtimer = 0;
			}
		}
		else OnDeath();
		UpdateCollider(0, 0, 32, 32);
	}

	if (invulnerable) {
		invulnerableCounter++;
		if (invulnerableCounter >= 60) {
			invulnerableCounter = 0;
			invulnerable = false;
		}
	}
	
	//interact with coal
	for (const auto& interactable : sceneManager->GetInteractables()) {
		if (interactable->GetInteractableType() == InteractableType::Coal 
			&& CheckCollisionRecs(interactable->GetInteractionZone(), GetCollider())) {
			interactable->Interact(*this);
		}
	}

	CollisionGround(sceneManager->GetTilemap());
	CollisionHead(sceneManager->GetTilemap());
	CollisionLeft(sceneManager->GetTilemap());
	CollisionRight(sceneManager->GetTilemap());

	
}

void TraitorBoss::Draw()
{
	activeState->Draw(*this);
}

void TraitorBoss::ReceiveDamage(int damage)
{
	this->health -= damage;
}

void TraitorBoss::OnDeath()
{
	markedDestroy = true;
}
