#include "ToastCat.h"

ToastCat::ToastCat(float pStartX, float pStartY) : Enemy(EnemyTypes::ToastCat)
{
	aTexture = LoadTexture("assets/graphics/Enemies/ToastCat.png");
	aToastTexture = LoadTexture("assets/graphics/Enemies/Toast.png");
	position.x = pStartX;
	position.y = pStartY;
}

void ToastCat::Update()
{
	aOnScreen = this->CheckOnScreen();
	if (aOnScreen == true)	//Cat Rendered
	{
		if (grounded == true)	//Cat is on the Ground
		{
			aEdgeSeekerLeft.x = position.x;
			aEdgeSeekerLeft.y = position.y + 33;
			aEdgeSeekerRight.x = position.x + 32;
			aEdgeSeekerRight.y = position.y + 33;
			aHasLineOfSight= this->CheckLineOfSight(position, playerCharacter->GetPosition(), sceneManager->GetTilemap());
			if (aHasLineOfSight==true)	//Cat on Ground and Sees Player
			{
				if (playerCharacter->GetPosition().x <= position.x)	//Cat sees the Player at its left
				{
					direction = LEFT;
				}
				else												//Cat sees Player at its right
				{
					direction = RIGHT;
				}
				if (this->GetDistance() <= aShootingRange)			//player is in shooting Distance
				{
					if (this->GetDistance() <= aDiscomfortRange)	//player is too close
					{
						sceneManager->GetTilemap();
						Rectangle tileRec = { 0,0,32,32 };
						for (const auto& collTile : tilemap->GetTileColliders()) 
						{
							tileRec.x = collTile.x;
							tileRec.y = collTile.y;
							if (direction == LEFT && CheckCollisionPointRec(aEdgeSeekerRight, tileRec))
							{
								position.x += aMovementSpeed;		//flees to the right if not on an Edge
							}
							else if (direction == RIGHT && CheckCollisionPointRec(aEdgeSeekerLeft, tileRec))
							{
								position.x -= aMovementSpeed;		//flees to the left if not on an Edge
							}
							else
							{
								if (aToastActive == false)
								{

								}
							}
						}
					}
				}
				
			}
		}
		else					//Cat is Not on the Ground
		{

		}
		aHitbox = { (float)position.x, (float)position.y, 32, 32 }
	}
}

void ToastCat::Draw()
{
	if (CheckCollisionRecs(playerCharacter->visibleScreen, this->aHitbox))
	{
		if (direction == LEFT)
		{
			DrawTexture(aTexture, position.x, position.y, WHITE);
		}
		else
		{
			DrawTexture(aTexture, position.x, position.y, WHITE);
		}
	}
	if (CheckCollisionRecs(playerCharacter->visibleScreen, this->aToastHitbox))
	{
		DrawTexture(aToastTexture, aToastPos.x, aToastPos.y, WHITE);
	}
}

ToastCat::~ToastCat()
{
}

void ToastCat::StartAttack()
{
	aToastActive = true;
	aToastPos.x = position.x + 12;
	aToastPos.y = position.y + 6;
	if (direction == LEFT)
	{
		Vector2 pPlayerposition = playerCharacter->GetPosition();
		if (pPlayerposition.y < position.y)
		{
			aTossYModifier = position.y - pPlayerposition.y;
		}
		else
		{
			aTossYModifier =pPlayerposition.x - position.x;
		}
	}
}
