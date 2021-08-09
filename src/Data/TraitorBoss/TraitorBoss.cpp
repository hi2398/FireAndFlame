#include "TraitorBoss.h"
#include "TraitorStateHandler.h"
#include "../../Scenes/TraitorBoss.h"


TraitorBoss::TraitorBoss(Vector2 location) : Enemy(EnemyTypes::Boss)
{
	health = 100;
	SetPosition(location);

	activeState = std::make_shared<TraitorStateHandler>(*this);
}

void TraitorBoss::Update()
{
	//decrease enemy health
	if (health > 0) {
		healthtimer++;
		if (healthtimer >= HEALTH_INTERVAL) {
			health--;
			healthtimer = 0;
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
