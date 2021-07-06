//
// Created by Adrian on 27/05/2021.
//

//
//Programmed by Robin on 23/06/2021 
//

#include "Enemy.h"

EnemyTypes Enemy::GetEnemyType() const {
	return aType;
}


void Enemy::RecieveDamage(int pDamage)
{
	aHealth -= pDamage;
}

bool Enemy::CheckLineOfSight(Vector2 pOrtsVector, Vector2 pRichtungsVector, const std::unique_ptr<Tilemap>& tilemap)
{
	Vector2 pLineOfSightVector;
	pLineOfSightVector.x = pRichtungsVector.x - pOrtsVector.x;
	pLineOfSightVector.y = pRichtungsVector.y - pOrtsVector.y;
	float distance = this->GetDistance(pOrtsVector, pRichtungsVector);
	Vector2 pEinheitsvector;
	pEinheitsvector.x = pLineOfSightVector.x / distance;
	pEinheitsvector.y = pLineOfSightVector.y / distance;
	for (Vector2 i = pOrtsVector; i.x != pRichtungsVector.x; i.x = i.x + pEinheitsvector.x) 
	{
		i.y = i.y + pEinheitsvector.y;

		sceneManager->GetTilemap();
		Rectangle tileRec = { 0,0,32,32 };
		for (const auto& collTile : tilemap->GetTileColliders()) {
			tileRec.x = collTile.x;
			tileRec.y = collTile.y;

			if (CheckCollisionPointRec(i, tileRec)) 
			{
				return true;
			}
			else SetGrounded(false);
			return false;
		}
	}
}

float Enemy::GetDistance(Vector2 pVector1, Vector2 pVector2)
{
	float x = pVector2.x - pVector1.x;	//Differenz auf der X Achse ermitteln
	if (x < 0) x = x * -1;				//Sichergehen, dass die Differenz positiv ist
	float y = pVector2.y - pVector1.y;	//Differenz auf der Y Achse ermitteln
	if (y <= 0) y = y * -1;				//Sichergehen dass die Differenz positiv ist
	float pDistance = sqrt(pow(x, 2) + pow(y, 2));
	return pDistance;
}

bool Enemy::CheckOnScreen()
{
	return CheckCollisionRecs(aHitbox, playerCharacter->visibleScreen);
}

bool Enemy::MakeDecision(int pProbability)
{
	int pChoice = rand() % 100 + 1;
	if (pProbability <= pChoice)
	{
		return true;
	}
	else
	{
		return false;
	}
}



Enemy::Enemy() : Actor(ObjectTypes::Enemy) {
	srand(time(NULL));
}
