#include "Enemy.h"
#include "../Global.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "raymath.h"


EnemyTypes Enemy::GetEnemyType() const {
	return enemyType;
}


void Enemy::ReceiveDamage(int damage)
{
    health -= damage;
	if (health == 0)
	{
		markedDestroy= true;
	}
}

bool Enemy::CheckLineOfSight(Vector2 startLocation, Vector2 endLocation, const std::unique_ptr<Tilemap>& tilemap)
{
	Vector2 lineOfSight = Vector2Subtract(endLocation, startLocation);

	Vector2 direction = Vector2Normalize(lineOfSight);
	Vector2 checkInterval = Vector2Scale(direction, 10);

	Vector2 nextCheckLocation = Vector2Add(startLocation, checkInterval);
	//see if next position to check is even in area of player
	while (CheckCollisionPointRec(nextCheckLocation, playerCharacter->visibleScreen))
	{
	    nextCheckLocation=Vector2Add(nextCheckLocation, checkInterval);
		Rectangle tileRec = { 0,0,32,32 };
		for (const auto& collTile : tilemap->GetTileColliders()) {
			tileRec.x = collTile.x;
			tileRec.y = collTile.y;

            //if line of sight hits opaque object, return
			if (CheckCollisionPointRec(nextCheckLocation, tileRec)) {
				return false;
			} //if raycast hits player, return true
			else if (CheckCollisionPointRec(nextCheckLocation, playerCharacter->playerHitbox)) {
			    std::cout << "Player found" << std::endl;
                return true;
			}
			break;
		}
	}
    return false;
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

#include "Enemy.h"


Enemy::Enemy(EnemyTypes enemyType) : Actor(ObjectTypes::Enemy) {
    this->enemyType=enemyType;
	srand(time(nullptr));
}
