#include "Enemy.h"
#include "../Global.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "raymath.h"

Enemy::Enemy(EnemyTypes enemyType) : Actor(ObjectTypes::Enemy) {
	this->enemyType = enemyType;
	srand(time(nullptr));
}



EnemyTypes Enemy::GetEnemyType() const {
	return enemyType;
}

EnemyState Enemy::GetEnemyState() {
	return state;
}

void Enemy::SetEnemyState(EnemyState state) {
	this->state = state;
}

float Enemy::GetEnemyMovementSpeed()
{
	return movementSpeed;
}


void Enemy::ReceiveDamage(int damage)
{
    health -= damage;
	if (health <= 0)
	{
		markedDestroy= true;
	}
}

float Enemy::GetDistance(Vector2 startLocation, Vector2 endLocation)
{
	return Vector2Distance(startLocation, endLocation);
}

bool Enemy::CheckOnScreen()
{
	return CheckCollisionRecs(hitbox, playerCharacter->visibleScreen);
}

bool Enemy::MakeDecision(int probability)
{
	int pChoice = rand() % 100 + 1;
	if (probability <= pChoice)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Enemy::UpdateCollider(float xOffset, float yOffset, float width, float height) {
	hitbox = { position.x + xOffset, position.y + yOffset, width, height };
}

Rectangle Enemy::GetCollider() const {
    return hitbox;
}

Texture2D Enemy::GetTexture() {
	return texture;
}

void Enemy::UpdateAttackHitbox()
{
	switch (GetDirection())
	{
	case LEFT:
		attackHitbox = { position.x - 20, position.y + 8, 1, 16 };
		break;
	case RIGHT:
		attackHitbox = { position.x + 32, position.y + 8, 1, 16 };
		break;
	default:
		break;
	}
}

Rectangle Enemy::GetAttackHitbox() {
	return attackHitbox;
}

bool Enemy::IsInvulnerable()
{
	return invulnerable;
}

void Enemy::SetInvulnerable(bool invulnerable)
{
	this->invulnerable = invulnerable;
}

int Enemy::GetDamageValue()
{
	return damageValue;
}

EnemyLevel Enemy::GetEnemyLevel() const
{
	return enemyLevel;
}
