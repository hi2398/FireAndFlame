#include "PlayerCharacter.h"
#include "raylib.h"
#include "PlayerObserver.h"
#include "IdleActionState.h"
#include "../../Global.h"
#include <stdexcept>

PlayerCharacter::PlayerCharacter() : Actor(ObjectTypes::Player) {
	texturePlayer = LoadTexture("assets/graphics/PLAYER.png");

	camera.target = { position.x + 20.0f, position.y + 20.0f };
	camera.offset = { 640, 360 };
	camera.rotation = 0.0f;
	camera.zoom = 2.0f;
	observer = std::make_shared<PlayerObserver>(*this);
	movementState = std::make_shared<MovementState>();
	actionState = std::make_shared<IdleActionState>();
	position = { 50 * 32, 36 * 32 };

	gravityMultiplier = 2.0;
}


void PlayerCharacter::Update() {
	
	movementState = movementState->Update(*this);
	actionState = actionState->Update(*this);

	
	CollisionLeft(sceneManager->GetTilemap());
	CollisionRight(sceneManager->GetTilemap());
	CollisionGround(sceneManager->GetTilemap());
	if (GetJumpCommand() || IsGrounded())CollisionHead(sceneManager->GetTilemap());

	//health cap
	if (health >= 100) health = 100;
	if (health <= 0) health = 0;

	//attack reset
	if (attackState > 0) {
		resetAttack++;
		if (resetAttack >= 90) attackState = 0;
	}

	//player hitbox update
	playerHitbox = { (float)position.x + 6, (float)position.y, playerWidth, playerHeight };
	
	//camera update
	camera.target = { position.x + 20.0f, position.y + 20.0f };

}

void PlayerCharacter::Draw() {
	//draw player
	DrawTexture(texturePlayer, static_cast<int>(position.x), static_cast<int>(position.y), WHITE);
	
	

	actionState->Draw(*this);
	movementState->Draw(*this);
}

int PlayerCharacter::GetHealth() const {
	return health;
}

void PlayerCharacter::SetHealth(int health) {
	this->health = health;
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


