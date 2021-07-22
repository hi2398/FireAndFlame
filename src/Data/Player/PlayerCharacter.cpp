#include "PlayerCharacter.h"
#include "raylib.h"
#include "PlayerObserver.h"
#include "IdleActionState.h"
#include "../../Global.h"
#include "MovementState.h"
#include <iostream>
#include "../../Scenes/DeathScreen.h"

PlayerCharacter::PlayerCharacter() : Actor(ObjectTypes::Player) {
	texturePlayer = LoadTexture("assets/graphics/PLAYER.png");
	textureWallSlide = LoadTexture("assets/graphics/PLAYER_WALL.png");

	spriteSheetMagmos = LoadTexture("assets/graphics/MagmosSpritesheet.png");

	camera.target = { position.x + 20.0f, position.y + 20.0f };
	camera.offset = { 640, 360 };
	camera.rotation = 0.0f;
	camera.zoom = 2.0f;
	observer = std::make_shared<PlayerObserver>(*this);
	movementState = std::make_shared<MovementState>();
	actionState = std::make_shared<IdleActionState>();
	position = { 0, 0 };

	gravityMultiplier = 2.0;

	canDoubleJump = true;
}


void PlayerCharacter::Update() {

	visibleScreen = { camera.target.x - (camera.offset.x / camera.zoom), camera.target.y - (camera.offset.y / camera.zoom), camera.offset.x * (2/camera.zoom), camera.offset.y * (2/camera.zoom)};

	if(!disablePlayerMovement){movementState = movementState->Update(*this);}

	actionState = actionState->Update(*this);


	//regularly decrease health
	if(isHealthDecreasing) {
        ++healthTimer;
        if (healthTimer >= HEALTH_INTERVAL) {
            healthTimer = 0;
            playerCharacter->SetHealth(playerCharacter->GetHealth() - 1);
        }
    }

	//world collision
	CollisionLeft(sceneManager->GetTilemap());
	CollisionRight(sceneManager->GetTilemap());
	CollisionGround(sceneManager->GetTilemap());
	CollisionHead(sceneManager->GetTilemap());

	//health cap
	if (health >= 100) health = 100;
	if (health <= 0) health = 0;

	//player invincibility frames
	if (invulnerable) {
		invulnerableCounter++;
		if (invulnerableCounter >= 60) {
			invulnerableCounter = 0;
			invulnerable = false;
		}
	}

	//player hitbox update
	playerHitbox = { (float)position.x + 6, (float)position.y, playerWidth, playerHeight };

	//camera update
	camera.target = { position.x + 20.0f, position.y + 20.0f };

	for (const auto& interactable : sceneManager->GetInteractables()) {
		if (CheckCollisionRecs(playerHitbox, interactable->GetInteractionZone())) {
			interactable->Interact(*this);
		}
	}
}

void PlayerCharacter::Draw() {
	actionState->Draw(*this);
	movementState->Draw(*this);
}

int PlayerCharacter::GetHealth() const {
	return health;
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

bool PlayerCharacter::IsInvulnerable()
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

void PlayerCharacter::ChangePlayerMovement(bool playerMovement) {
    disablePlayerMovement = playerMovement;
}


