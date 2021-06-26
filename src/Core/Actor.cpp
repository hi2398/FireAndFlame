#include <raylib.h>
#include <raymath.h>
#include "Actor.h"

Actor::Actor(ObjectTypes type) : Object(type), lastTickPos(position) {

}

void Actor::SetLastPosition(Vector2 position) {
    lastTickPos = position;
}

Vector2 Actor::GetLastPosition() {
    return lastTickPos;
}


void Actor::Jump() {
    position.y -= 1.0f;
}

Direction Actor::GetDirection() const {
    return direction;
}

float Actor::GetGravityMultiplier() {
    return gravityMultiplier;
}

void Actor::SetGrounded(bool grounded)
{
    this->grounded = grounded;
}

bool Actor::IsGrounded() {
    return grounded;
}

void Actor::SetJumpCommand(bool jumpUp) {
    this->jumpUp = jumpUp;
}

bool Actor::GetJumpCommand() {
    return jumpUp;
}

MOVEMENT Actor::GetNextMovement() {
    MOVEMENT tmp = nextMovement;
    nextMovement = MOVEMENT::IDLE;
    return tmp;
}

void Actor::SetNextMovement(MOVEMENT movement) {
    nextMovement = movement;
}

bool Actor::GetWallCollisionLeft() {
    return hugWallLeft;
}

void Actor::SetWallCollisionLeft(bool hugWallLeft) {
    this->hugWallLeft = hugWallLeft;
}

bool Actor::GetWallCollisionRight() {
    return hugWallRight;
}

void Actor::SetWallCollisionRight(bool hugWallRight) {
    this->hugWallRight = hugWallRight;
}

float Actor::GetFallingSpeed() {
    return fallingSpeed;
}

void Actor::SetFallingSpeed(float fallingSpeed) {
    this->fallingSpeed = fallingSpeed;
}

int Actor::GetTimesJumped()
{
    return timesJumped;
}

void Actor::SetTimesJumped(int timesJumped)
{
    this->timesJumped = timesJumped;
}

bool Actor::GetCanDoubleJump()
{
    return canDoubleJump;
}

void Actor::SetCanDoubleJump(bool canDoubleJump)
{
    this->canDoubleJump = canDoubleJump;
}

bool Actor::GetIsRunning()
{
    return isRunning;
}

void Actor::SetIsRunning(bool isRunning)
{
    this->isRunning = isRunning;
}

bool Actor::GetHeadCollision() {
    return headCollision;
}

void Actor::SetHeadCollision(bool headCollision) {
    this->headCollision = headCollision;
}

float Actor::GetJumpSpeed() {
    return jumpSpeed;
}

void Actor::SetJumpSpeed(float jumpSpeed) {
    this->jumpSpeed = jumpSpeed;
}

void Actor::CollisionGround(const std::unique_ptr<Tilemap>& tilemap)
{
	//tile rectangles
	Rectangle tileRec = { 0,0,32,32 };

	//player vector alias
	const auto lastPos = GetLastPosition();
	const auto newPos = GetPosition();

	for (const auto& collTile : tilemap->GetTileColliders()) {
		tileRec.x = collTile.x;
		tileRec.y = collTile.y;

		//player coll ground
		Rectangle playerFeet = { newPos.x, newPos.y + 32, 32, 1 };

		if (CheckCollisionRecs(tileRec, playerFeet)) {
			SetGrounded(true);
			SetPosition({ newPos.x, tileRec.y - 32.0f });
			return;
		}
		else SetGrounded(false);
	}
}

void Actor::CollisionLeft(const std::unique_ptr<Tilemap>& tilemap) {
	//tile rectangles
	Rectangle tileRec = { 0,0,32,32 };

	//player vector alias
	const auto lastPos = GetLastPosition();
	const auto newPos = GetPosition();

	for (const auto& collTile : tilemap->GetTileColliders()) {
		tileRec.x = collTile.x;
		tileRec.y = collTile.y;

		//player coll left
		Rectangle playerLeftSide = { newPos.x - 1, newPos.y + 6, 1, 20 };

		if (CheckCollisionRecs(tileRec, playerLeftSide)) {
			SetWallCollisionLeft(true);
			SetPosition({ tileRec.x + 32, newPos.y });
			return;
		}
		else {
			SetWallCollisionLeft(false);
		}
	}
}

void Actor::CollisionRight(const std::unique_ptr<Tilemap>& tilemap) {
	//tile rectangles
	Rectangle tileRec = { 0,0,32,32 };

	//player vector alias
	const auto lastPos = GetLastPosition();
	const auto newPos = GetPosition();

	for (const auto& collTile : tilemap->GetTileColliders()) {
		tileRec.x = collTile.x;
		tileRec.y = collTile.y;

		//player coll right
		Rectangle playerRightSide = { newPos.x + 32, newPos.y + 6, 1, 20 };

		if (CheckCollisionRecs(tileRec, playerRightSide)) {
			SetWallCollisionRight(true);
			SetPosition({ tileRec.x - 32, newPos.y });
			return;
		}
		else {
			SetWallCollisionRight(false);
		}
	}
}

void Actor::CollisionHead(const std::unique_ptr<Tilemap>& tilemap) {
	//tile rectangles
	Rectangle tileRec = { 0,0,32,32 };

	//player vector alias
	const auto lastPos = GetLastPosition();
	const auto newPos = GetPosition();

	for (const auto& collTile : tilemap->GetTileColliders()) {
		tileRec.x = collTile.x;
		tileRec.y = collTile.y;

		//player coll head
		Rectangle playerUpperSide = { newPos.x , newPos.y - 1, 32, 1 };

		if (CheckCollisionRecs(tileRec, playerUpperSide)) {
			SetHeadCollision(true);
			SetJumpCommand(false);
			SetPosition({ newPos.x, tileRec.y + 32 });
			return;
		}
		else {
			SetHeadCollision(false);
		}
	}
}