#include "Enemy.h"
#include "../Global.h"
#include <cstdlib>
#include <ctime>
#include <cmath>


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
	Vector2 pLineOfSightVector;
	pLineOfSightVector.x = endLocation.x - startLocation.x;
	pLineOfSightVector.y = endLocation.y - startLocation.y;
	float distance = this->GetDistance(startLocation, endLocation);
	Vector2 pUnitvector;
	pUnitvector.x = pLineOfSightVector.x / distance;
	pUnitvector.y = pLineOfSightVector.y / distance;
	Vector2 i = startLocation;
	if (CheckCollisionPointRec(i, playerCharacter->visibleScreen))
	{
		i.x =i.x+ pUnitvector.x*20;
		i.y =i.y+ pUnitvector.y*20;
		Rectangle tileRec = { 0,0,32,32 };
		for (const auto& collTile : tilemap->GetTileColliders()) {
			tileRec.x = collTile.x;
			tileRec.y = collTile.y;
			if (CheckCollisionPointRec(i, playerCharacter->playerHitbox))
			{
				return true;
			}
			else if (CheckCollisionPointRec(i, tileRec)||!CheckCollisionPointRec(i, playerCharacter->visibleScreen))
			{
				std::cout << "Ja wo isser denn?\n";
                return false;
			}
			else
			{
				break;
			}
		}
	}
}

float Enemy::GetDistance(Vector2 startLocation, Vector2 endLocation)
{
	float x = endLocation.x - startLocation.x;	//Differenz auf der X Achse ermitteln
	float y = endLocation.y - startLocation.y;	//Differenz auf der Y Achse ermitteln
	float pDistance = sqrt(pow(x, 2) + pow(y, 2));
	return pDistance;
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
