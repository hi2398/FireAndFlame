#include "../../Global.h"

#include "TraitorBoss.h"
#include "TraitorStateHandler.h"
#include "../../Scenes/TraitorBoss.h"


TraitorBoss::TraitorBoss(Vector2 location) : Enemy(EnemyTypes::Boss)
{
	canUseCoal = true;
	health = MAX_HEALTH;
	SetPosition(location);

	activeState = std::make_shared<TraitorStateHandler>(*this);
}

void TraitorBoss::Update()
{
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
		UpdateCollider(0, 0, 32, 32);
	}
	
	//interact with coal
	for (const auto& interactable : sceneManager->GetInteractables()) {
		if (interactable->GetInteractableType() == InteractableType::Coal 
			&& CheckCollisionRecs(interactable->GetInteractionZone(), GetCollider())) {
			interactable->Interact(*this);
		}
	}

	activeState->Update(*this);
}

void TraitorBoss::Draw()
{
	activeState->Draw(*this);
}

void TraitorBoss::ReceiveDamage(int damage)
{
	this->health -= damage;
}