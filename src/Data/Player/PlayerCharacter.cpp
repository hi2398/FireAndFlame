#include "PlayerCharacter.h"
#include "raylib.h"
#include "PlayerObserver.h"
#include "IdleActionState.h"
#include "../../Global.h"
#include "MovementState.h"
#include <iostream>
#include "../../Scenes/DeathScreen.h"

PlayerCharacter::PlayerCharacter() : Actor(ObjectTypes::Player) {
	upperBody = LoadTexture("assets/graphics/MagmosUpperBody.png");
	lowerBody = LoadTexture("assets/graphics/MagmosLegs.png");
	attackSprite = LoadTexture("assets/graphics/AttackSprites.png");

	camera.target = { position.x + 20.0f, position.y + 20.0f };
	camera.offset = { 640, 360 };
	camera.rotation = 0.0f;
	camera.zoom = 2.0f;


	
	position = { 0, 0 };

	gravityMultiplier = 2.0;
	health = max_health;
	canDoubleJump = true;

	observer = std::make_shared<PlayerObserver>(*this);
	movementState = std::make_shared<MovementState>(*this);
	actionState = std::make_shared<IdleActionState>(*this);

    if constexpr (DEBUG_BUILD){
        abilitiesUnlocked=AbilitiesUnlocked::Doublejump; //unlock all abilites if in debug mode
    }
}


void PlayerCharacter::Update() {
	visibleScreen = { camera.target.x - (camera.offset.x / camera.zoom), camera.target.y - (camera.offset.y / camera.zoom), camera.offset.x * (2/camera.zoom), camera.offset.y * (2/camera.zoom)};

	{movementState = movementState->Update(*this); }

	actionState = actionState->Update(*this);

	//animation frame counter
	playerFrameCounter++;
	if (playerFrameCounter >= 10) {
		currentFrame++;
		playerFrameCounter = 0;
	}

	//regularly decrease health
	if(isHealthDecreasing) {
        ++healthTimer;
        if (healthTimer >= HEALTH_INTERVAL) {
            healthTimer = 0;
            playerCharacter->SetHealth(playerCharacter->GetHealth() - 1);
        }
    }

	//dash cooldown
	if (!dashIsReady) {
		dashCounter++;
		if (dashCounter >= DASH_COOLDOWN) {
			dashCounter = 0;
			dashIsReady = true;
		}
	}

	//world collision
	groundedLastFrame = IsGrounded();
	CollisionLeft(sceneManager->GetTilemap(), GetType());
	CollisionRight(sceneManager->GetTilemap(), GetType());
	CollisionGround(sceneManager->GetTilemap(), GetType());
	CollisionHead(sceneManager->GetTilemap(), GetType());

	//health cap
	if (health >= 100) health = 100;
	if (health <= 0) health = 0;

	//player invincibility frames
	if (invulnerable) {
		invulnerableCounter++;

		if (invulnerableCounter % 4) {
			invulnerableVisualized=!invulnerableVisualized;
		}

		if (invulnerableCounter >= 60) {
			invulnerableCounter = 0;
			invulnerableVisualized = false;
			invulnerable = false;
		}
	}

	//player hitbox update
	playerHitbox = { (float)position.x + 6, (float)position.y, playerWidth, playerHeight };

	//camera update
	if (followCam) camera.target = { position.x + 20.0f, position.y + 20.0f };

	for (const auto& interactable : sceneManager->GetInteractables()) {
		if (CheckCollisionRecs(playerHitbox, interactable->GetInteractionZone())) {
			interactable->Interact(*this);
		}
	}

	for (const auto& enemies : sceneManager->GetEnemies()) {
		if (CheckCollisionRecs(playerHitbox, enemies->GetCollider()) && enemies->GetEnemyType() != EnemyTypes::Saugi) {
			if (!playerCharacter->IsInvulnerable()) playerCharacter->SetInvulnerable(true), playerCharacter->SetHealth(playerCharacter->GetHealth() - enemies->GetDamageValue());
		}
	}
	
	nextMovement = MOVEMENT::IDLE;

	if constexpr (DEBUG_PLAYER_POSITION) 	std::cout << position.x / 32 << "\t" << position.y / 32 << "\n";
}

void PlayerCharacter::Draw() {
	if (!invulnerableVisualized) {
		movementState->Draw(*this);
		actionState->Draw(*this);
	}
	
}

int PlayerCharacter::GetHealth() const {
	return this->health;
}

void PlayerCharacter::SetHealth(int health) {
	this->health = health;
	if (health <= 0) {
		//sceneManager->SetNextScene(std::make_unique<DeathScreen>()); TODO enable me when save and load is finished
	}
}


Observer& PlayerCharacter::GetObserver() const {
	return *observer;
}

ACTION PlayerCharacter::GetNextAction() {
	ACTION tmp = nextAction;
	nextAction = ACTION::NONE; //clear out the action so it doesnt trigger again
	return tmp;
}

void PlayerCharacter::SetNextAction(ACTION action) {
	nextAction = action;
}

bool PlayerCharacter::IsInvulnerable() const
{
	return invulnerable;
}

void PlayerCharacter::SetInvulnerable(bool invulnerable)
{
	this->invulnerable = invulnerable;
}

const int PlayerCharacter::GetMaxHealth() {
	return max_health;
}

void PlayerCharacter::BlockPlayerControls(bool blockThis) {
	controlsBlocked = blockThis;
}

bool PlayerCharacter::InputDisabled() const
{
	return controlsBlocked;
}

void PlayerCharacter::ChangeCameraControl()
{
    followCam=!followCam;
}

bool PlayerCharacter::DashReady() const
{
	return dashIsReady;
}

void PlayerCharacter::SetDashIsReady(bool ready)
{
	this->dashIsReady = ready;
}

bool PlayerCharacter::GetLastTickGroundedState() const
{
	return groundedLastFrame;
}

int PlayerCharacter::GetFrame() const {
	return playerFrameCounter;
}

int PlayerCharacter::GetCurrentFrame() const {
	return currentFrame;
}

AbilitiesUnlocked PlayerCharacter::GetUnlockedAbilities() const {
    return abilitiesUnlocked;
}

void PlayerCharacter::SetUnlockedAbilityLevel(AbilitiesUnlocked abilitiesUnlocked) {
    this->abilitiesUnlocked=abilitiesUnlocked;

}
