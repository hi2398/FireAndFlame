#include "../../Global.h"

#include "TraitorBoss.h"
#include "TBBeforeFightState.h"
#include "TBIdleState.h"
#include "TBAfterFightState.h"
#include "../../Scenes/TraitorBossScene.h"


TraitorBoss::TraitorBoss(Vector2 location) : Enemy(EnemyTypes::Boss)
{
	canUseCoal = true;
	health = MAX_HEALTH;
	movementSpeed = 3.0f;
	SetPosition(location);
	SetDirection(LEFT);
	gravityMultiplier = 2.0f;

	activeState = std::make_shared<TBBeforeFightState>(*this);
	texture = LoadTexture("assets/Bosses/TraitorBoss/TraitorUpperBody.png");
	texture2 = LoadTexture("assets/Bosses/TraitorBoss/TraitorLegs.png");
	texture3 = LoadTexture("assets/Bosses/TraitorBoss/AttackSprites.png");
}

void TraitorBoss::Update()
{
	activeState = activeState->Update(*this);

	if (actionCounter >= 2) cooldown--;
	if (cooldown == 0) {
		actionCounter = 0;
		cooldown = 240;
	}

	hud->SetBossEnemyHealth(health, 3);
	if (health < MAX_HEALTH && !isFighting) fightStarted = true;
	if (fightStarted || isFighting) {
		isFighting = true;
		fightStarted = false;
		if (IsGrounded()) {
			SetJumpCommand(false);
			SetJumpSpeed(5.0f);
			SetFallingSpeed(0.0f);
		}
		else if (!GetJumpCommand() && !IsGrounded()) {
			position.y += GetFallingSpeed();
			SetFallingSpeed(GetFallingSpeed() + 0.1f * GetGravityMultiplier());
		}
		UpdateCollider(0, 0, 32, 32);
	}

	//decrease enemy health
	if (isFighting && health > 0) {
		healthtimer++;
		if (healthtimer >= HEALTH_INTERVAL) {
			health--;
			healthtimer = 0;
		}
	}
	else {
		UpdateCollider(0,0,0,0); //erase hitbox after fight
		isFighting = false;
		OnDeath();
	}

	if (invulnerable) {
		invulnerableCounter++;
		if (invulnerableCounter >= 30) {
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

	CollisionGround(sceneManager->GetTilemap(), ObjectTypes::Player);
	CollisionHead(sceneManager->GetTilemap(), ObjectTypes::Player);
	CollisionLeft(sceneManager->GetTilemap(), ObjectTypes::Player);
	CollisionRight(sceneManager->GetTilemap(), ObjectTypes::Player);

	
}

void TraitorBoss::Draw()
{
	activeState->Draw(*this);
}

void TraitorBoss::ReceiveDamage(int damage)
{
	this->health -= damage;
}

TraitorBoss::~TraitorBoss()
{
	UnloadTexture(texture);
	UnloadTexture(texture2);
	UnloadTexture(texture3);
}

void TraitorBoss::OnDeath()
{
	playerCharacter->SetHealth(100);
}
