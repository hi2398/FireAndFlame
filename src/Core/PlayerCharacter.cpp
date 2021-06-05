//
// Created by Adrian on 27/05/2021.
//
// test push 05062021

#include "PlayerCharacter.h"
#include "raylib.h"

PlayerCharacter::PlayerCharacter() : Actor(ObjectTypes::Player) {
	texturePlayer = LoadTexture("assets/graphics/PLAYER.png");

	camera.target = { vectorPlayer.x + 20.0f, vectorPlayer.y + 20.0f };
	camera.offset = { 640, 360 };
	camera.rotation = 0.0f;
	camera.zoom = 2.0f;
}


void PlayerCharacter::Update() {
	//camera update
	camera.target = { vectorPlayer.x + 20.0f, vectorPlayer.y + 20.0f };
	//attack reset
	if (attackState > 0) {
		resetAttack++;
		if (resetAttack >= 90) attackState = 0, spearRotation = 300;
	}
	//player hitbox update
	playerHitbox = { (float)vectorPlayer.x, (float)vectorPlayer.y, 32, 32 };

	//spear follows player
	spearHitbox.x = vectorPlayer.x + 25.0f;
	spearHitbox.y = vectorPlayer.y + 11.0f;
	this->RunAttack();
	this->RunChargedAttack();
	this->RunFireball();
	this->RunJump();
}

void PlayerCharacter::Draw() {
		//draw player
		DrawTexture(texturePlayer, vectorPlayer.x, vectorPlayer.y, WHITE);
		//Draw Attacks (Hitboxes)
		if (isSwiping) {
			DrawRectanglePro(spearHitbox, { 10, 0 }, spearRotation, RED);
		}

		if (isShootingFireball) {
			DrawCircle(vectorFireball.x, vectorFireball.y, 8.0f, RED);
		}

		if (isCharged) {
			DrawRectanglePro(spearHitbox, { spearHitbox.width / 2 , 2 }, spearRotation, RED);
		}
}

void PlayerCharacter::Move(int direction) {
	vectorPlayer.x += 3.0f * direction;
}

void PlayerCharacter::Jump() {
	if (isGrounded) vectorPlayer.y = 8.00f;
	isJumping = true;
	jumpState++;
	switch (canDoubleJump)
	{
	case 0: //simple Jump
		if (jumpState < 1) verticalSpeed = -5.0f;
		break;
	case 1: //double Jump
		if (jumpState < 2) verticalSpeed = -5.0f;
		break;
	default:
		break;
	}
	
}

void PlayerCharacter::RunJump() {
	if (isGrounded) {
		if (isAirborne)isJumping = false, isAirborne = false;
		jumpState = 0;
		vectorPlayer.y = 40.0f - texturePlayer.height + 1.0f;
	}

	if (isJumping && isGrounded) {
		vectorPlayer.y = 40.0f - texturePlayer.height;
		isAirborne = true;
	}

	if (!isGrounded) {
		vectorPlayer.y += verticalSpeed;
		verticalSpeed += 0.1f * gravityMultiplier;
	}

}

void PlayerCharacter::Attack() {
	attackCommand = true;
	chargedAttackCommand = false;
}

void PlayerCharacter::RunAttack() {
	if (attackCommand) {
		if (!isSwiping && !isCharged) isSwiping = true, resetAttack = 0;

		//attack states
		switch (attackState)
		{
		case 0:
			if (isSwiping) {
				spearRotation += 10.0f;
				if (spearRotation >= 410) {
					spearRotation = 330;
					isSwiping = false;
					attackCommand = false;
					attackState++;
				}
			}
			break;
		case 1:
			if (isSwiping) {
				spearRotation += 3.0f;
				if (spearRotation >= 390) {
					spearRotation = 300;
					isSwiping = false;
					attackCommand = false;
					attackState++;
				}
			}
			break;
		case 2:
			//stab
			if (isSwiping) {
				spearRotation = 0;
				stabbingDistance += 5.0f;

				if (stabbingDistance <= 45) {
					spearHitbox.x += 15.0f * stabbingDistance / 45;
				}

				if (stabbingDistance > 45) {
					spearHitbox.x += 15.0f * (float)((90 - stabbingDistance) / 45);
				}

				if (stabbingDistance >= 90) {
					stabbingDistance = 0;
					isSwiping = false;
					attackCommand = false;
					spearRotation = 300;
					attackState = 0;
				}
			}
			break;
		default:
			break;
		}
	}


}

void PlayerCharacter::Fireball() {
	fireballCommand = true;
	if (!isShootingFireball) {
		vectorFireball.x = vectorPlayer.x + 25;
		vectorFireball.y = vectorPlayer.y + 11;
	}
	
}

void PlayerCharacter::RunFireball() {
	if (fireballCommand) {
		isShootingFireball = true;
		if (isShootingFireball) {
			vectorFireball.x += 10.0f;
			if (vectorFireball.x > ((float)GetScreenWidth() / 2) + vectorPlayer.x) isShootingFireball = false, fireballCommand = false;
		}
	}

}

void PlayerCharacter::ChargingAttack() {
	chargingCounter++;
}

void PlayerCharacter::ChargedAttack() {
	chargedAttackCommand = true;
	if (chargedAttackCommand && chargingCounter / 60 >= 2) isCharged = true;
	chargingCounter = 0;
}

void PlayerCharacter::RunChargedAttack() {

	if (isCharged) {

		//charged rotation
		spearRotation += 40.0f;

		if (spearRotation <= 840) {
			spearHitbox.x += 5.0f * spearRotation / 100;
		}
		if (spearRotation > 840) {
			spearHitbox.x += 5.0f * (1380 - spearRotation) / 100;
		}



		if (spearRotation >= 1380) {
			spearRotation = 300;
			isCharged = false;
			chargedAttackCommand = false;
		}
	}


}

int PlayerCharacter::GetHealth() const {
    return health;
}

void PlayerCharacter::SetHealth(int health) {
    this->health=health;
}