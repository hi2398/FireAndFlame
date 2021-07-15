#include "ToastCat.h"
#include "../../Global.h"


ToastCat::ToastCat(Vector2 initialPos) : Enemy(EnemyTypes::ToastCat)
{
    texture = LoadTexture("assets/graphics/Enemies/ToastCat.png");
    toastTexture = LoadTexture("assets/graphics/Enemies/Toast.png");
	position.x = initialPos.x;
	position.y = initialPos.y;
}

void ToastCat::Update()
{
	onScreen = this->CheckOnScreen();
	if (onScreen)	//Cat Rendered
	{
		if (grounded)	//Cat is on the Ground
		{
            edgeSeekerLeft.x = position.x;
            edgeSeekerLeft.y = position.y + 33;
            edgeSeekerRight.x = position.x + 32;
            edgeSeekerRight.y = position.y + 33;
            hasLineOfSight= this->CheckLineOfSight(position, playerCharacter->GetPosition(), sceneManager->GetTilemap());
			if (hasLineOfSight)	//Cat on Ground and Sees Player
			{
				if (playerCharacter->GetPosition().x <= position.x)	//Cat sees the Player at its left
				{
					direction = LEFT;
				}
				else												//Cat sees Player at its right
				{
					direction = RIGHT;
				}

				/*
				if (this->GetDistance() <= shootingRange)			//player is in shooting Distance
				{
					if (this->GetDistance() <= discomfortRange)	//player is too close
					{
						Rectangle tileRec = { 0,0,32,32 };
						for (const auto& collTile : sceneManager->GetTilemap()->GetTileColliders())
						{
							tileRec.x = collTile.x;
							tileRec.y = collTile.y;
							if (direction == LEFT && CheckCollisionPointRec(edgeSeekerRight, tileRec))
							{
								position.x += movementSpeed;		//flees to the right if not on an Edge
							}
							else if (direction == RIGHT && CheckCollisionPointRec(edgeSeekerLeft, tileRec))
							{
								position.x -= movementSpeed;		//flees to the left if not on an Edge
							}
							else
							{
								if (!toastActive)
								{

								}
							}
						}
					}
				}
				*/
				
			}
		}
		else					//Cat is Not on the Ground
		{

		}
        hitbox = {(float)position.x, (float)position.y, 32, 32 };
	}
}

void ToastCat::Draw()
{
	if (CheckCollisionRecs(playerCharacter->visibleScreen, this->hitbox))
	{
		if (direction == LEFT)
		{
			DrawTexture(texture, position.x, position.y, WHITE);
		}
		else
		{
			DrawTexture(texture, position.x, position.y, WHITE);
		}
	}
	if (CheckCollisionRecs(playerCharacter->visibleScreen, this->toastHitbox))
	{
		DrawTexture(toastTexture, toastPos.x, toastPos.y, WHITE);
	}
}

ToastCat::~ToastCat()
{
}

void ToastCat::StartAttack()
{
    toastActive = true;
    toastPos.x = position.x + 12;
    toastPos.y = position.y + 6;
	if (direction == LEFT)
	{
		Vector2 pPlayerposition = playerCharacter->GetPosition();
		if (pPlayerposition.y < position.y)
		{
            tossYModifier = position.y - pPlayerposition.y;
		}
		else
		{
            tossYModifier = pPlayerposition.x - position.x;
		}
	}
}
