#include <raylib.h>
#include <raymath.h>
#include "Actor.h"
#include "../Global.h"

Actor::Actor(ObjectTypes type) : Object(type), lastTickPos(position) {

}

void Actor::SetLastPosition(Vector2 position) {
    lastTickPos = position;
}

Vector2 Actor::GetLastPosition() {
    return lastTickPos;
}

Direction Actor::GetDirection() const {
    return direction;
}


float Actor::GetGravityMultiplier() const {
    return gravityMultiplier;
}

void Actor::SetGrounded(bool grounded)
{
    this->grounded = grounded;
}

bool Actor::IsGrounded() const {
    return grounded;
}

void Actor::SetJumpCommand(bool jumpUp) {
    this->jumpUp = jumpUp;
}

bool Actor::GetJumpCommand() const {
    return jumpUp;
}

MOVEMENT Actor::GetNextMovement() {
    return nextMovement;
}

void Actor::SetNextMovement(MOVEMENT movement) {
	if (movement == MOVEMENT::MOVE_LEFT) direction = LEFT;
	if (movement == MOVEMENT::MOVE_RIGHT) direction = RIGHT;
    nextMovement = movement;
}

bool Actor::GetWallCollisionLeft() const {
    return hugWallLeft;
}

void Actor::SetWallCollisionLeft(bool hugWallLeft) {
    this->hugWallLeft = hugWallLeft;
}

bool Actor::GetWallCollisionRight() const {
    return hugWallRight;
}

void Actor::SetWallCollisionRight(bool hugWallRight) {
    this->hugWallRight = hugWallRight;
}

float Actor::GetFallingSpeed() const {
    return fallingSpeed;
}

void Actor::SetFallingSpeed(float fallingSpeed) {
    this->fallingSpeed = fallingSpeed;
}

int Actor::GetTimesJumped() const
{
    return timesJumped;
}

void Actor::SetTimesJumped(int timesJumped)
{
    this->timesJumped = timesJumped;
}

bool Actor::GetCanDoubleJump() const
{
    return canDoubleJump;
}

void Actor::SetCanDoubleJump(bool canDoubleJump)
{
    this->canDoubleJump = canDoubleJump;
}

bool Actor::GetIsRunning() const
{
    return isRunning;
}

void Actor::SetIsRunning(bool isRunning)
{
    this->isRunning = isRunning;
}

bool Actor::GetHeadCollision() const {
    return headCollision;
}

void Actor::SetHeadCollision(bool headCollision) {
    this->headCollision = headCollision;
}

float Actor::GetJumpSpeed() const {
    return jumpSpeed;
}

void Actor::SetJumpSpeed(float jumpSpeed) {
    this->jumpSpeed = jumpSpeed;
}

bool Actor::GetWallJumpCommand() const {
	return jumpOffWall;
}

void Actor::SetWallJumpCommand(bool jumpOffWall) {
	this->jumpOffWall = jumpOffWall;
}

bool Actor::GetJumpBlocked() const {
	return jumpBlocked;
}

void Actor::SetJumpBlocked(bool jumpBlocked) {
	this->jumpBlocked = jumpBlocked;
}

int Actor::GetWallCounter() const {
	return wallCounter;
}

void Actor::SetWallCounter(int wallCounter) {
	this->wallCounter = wallCounter;
}

bool Actor::GetIsDashing() const {
	return isDashing;
}

void Actor::SetIsDashing(bool isDashing) {
	this->isDashing = isDashing;
}

Vector2 Actor::Dash(int direction) {
	dashCounter++;
	isDashing = true;
	position.x += dashDistance * direction / 12;
	if (dashCounter >= 12) {
		isDashing = false;
		dashCounter = 0;
	}
	return position;
}

void Actor::DrawDirectional(Vector2 location, Texture2D texture, Rectangle sourceRec) const {
    DrawTextureRec(texture,
                   { sourceRec.x,
                     sourceRec.y,
                     (float) sourceRec.width * GetDirection(),
                     (float) sourceRec.height },
                   location,
                   WHITE);
}

int Actor::GetHealth() const
{
	return health;
}

void Actor::SetHealth(int health)
{
	this->health = health;
}

bool Actor::CanUseCoal() const
{
	return canUseCoal;
}

bool Actor::GetCanDash() const
{
	return canDash;
}

void Actor::SetCanDash(bool canDash)
{
	this->canDash = canDash;
}

AttackDirection Actor::GetAttackDirection() const
{
	return attackDirection;
}

void Actor::SetAttackDirection(Direction direction)
{
	if (direction == LEFT) attackDirection = ATT_LEFT;
	if (direction == RIGHT) attackDirection = ATT_RIGHT;
}

bool Actor::GetIsSwiping() const
{
	return isSwiping;
}

void Actor::SetIsSwiping(bool isSwiping)
{
	this->isSwiping = isSwiping;
}

bool Actor::GetActionBlocked() const
{
	return actionBlocked;
}

void Actor::SetActionBlocked(bool actionBlocked)
{
	this->actionBlocked = actionBlocked;
}


void Actor::SetDirection(Direction direction) {
	this->direction = direction;
}

void Actor::CollisionGround(const std::unique_ptr<Tilemap>& tilemap)
{
	//tile rectangles
	Rectangle tileRec = { 0,0,32,32 };

	//player vector alias
	const auto newPos = GetPosition();

	for (const auto& collTile : tilemap->GetTileColliders()) {
		tileRec.x = collTile.x;
		tileRec.y = collTile.y;

		//player coll ground
		Rectangle playerFeet = { newPos.x, newPos.y + 32, 32, 0.5 };

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
	const auto newPos = GetPosition();

	for (const auto& collTile : tilemap->GetTileColliders()) {
		tileRec.x = collTile.x;
		tileRec.y = collTile.y;

		//player coll left
		Rectangle playerLeftSide = { newPos.x - 0.5, newPos.y + 6, 0.5, 20 };

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
	const auto newPos = GetPosition();

	for (const auto& collTile : tilemap->GetTileColliders()) {
		tileRec.x = collTile.x;
		tileRec.y = collTile.y;

		//player coll right
		Rectangle playerRightSide = { newPos.x + 32, newPos.y + 6, 0.5, 20 };

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
	const auto newPos = GetPosition();

	for (const auto& collTile : tilemap->GetTileColliders()) {
		tileRec.x = collTile.x;
		tileRec.y = collTile.y;

		//player coll head
		Rectangle playerUpperSide = { newPos.x , newPos.y - 0.5, 32, 0.5 };

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

void Actor::LookAtPlayer() {
    if ((playerCharacter->GetPosition().x- GetPosition().x) <0) {
        SetDirection(LEFT);
    } else SetDirection(RIGHT);

}