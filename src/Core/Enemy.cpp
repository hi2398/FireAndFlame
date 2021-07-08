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
	Vector2 pEinheitsvector;
	pEinheitsvector.x = pLineOfSightVector.x / distance;
	pEinheitsvector.y = pLineOfSightVector.y / distance;
	for (Vector2 i = startLocation; i.x != endLocation.x; i.x = i.x + pEinheitsvector.x)
	{
		i.y = i.y + pEinheitsvector.y;

		Rectangle tileRec = { 0,0,32,32 };
		for (const auto& collTile : tilemap->GetTileColliders()) {
			tileRec.x = collTile.x;
			tileRec.y = collTile.y;

			if (CheckCollisionPointRec(i, tileRec)) 
			{
				return true;
			}
			else {
                SetGrounded(false);
                return false;
            }
		}
	}
}

float Enemy::GetDistance(Vector2 startLocation, Vector2 endLocation)
{
	float x = endLocation.x - startLocation.x;	//Differenz auf der X Achse ermitteln
	if (x < 0) x = x * -1;				//Sichergehen, dass die Differenz positiv ist
	float y = endLocation.y - startLocation.y;	//Differenz auf der Y Achse ermitteln
	if (y <= 0) y = y * -1;				//Sichergehen dass die Differenz positiv ist
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



Enemy::Enemy(EnemyTypes enemyType) : Actor(ObjectTypes::Enemy) {
    this->enemyType=enemyType;
	srand(time(NULL));
}
