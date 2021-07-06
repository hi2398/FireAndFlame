#include "Miner.h"

Miner::Miner(float pStartX, float pStartY): Enemy(EnemyTypes::Miner)
{
	aTexture = LoadTexture("assets/graphics/Enemies/Miner.png");
	position.x = pStartX;
	position.y = pStartY;
	aHitbox.x = pStartX;
	aHitbox.y = pStartY;
	aHitbox.width = 32;
	aHitbox.height = 32;
	aStunCounter = aStunDuration;
	aAttackCounter = aAttackDuration;
	aSeekingcounter = aSeekingDuration;
	aAttackArea.height = 15;
	aAttackArea.width = 26;
}

void Miner::Update()
{
	aOnScreen = this->CheckOnScreen();
	if (aOnScreen == true)//Wird Gerendert
	{
		if (grounded == true)//ist auf dem Boden
		{
			if (aState == 4)//Ist gestunned
			{
				--aStunCounter;
				if (aStunCounter == 0)
				{
					aStunCounter = aStunDuration;
					aState = 0;
				}
			}
			else//Ist nicht gestunned
			{

				aHasLineOfSight = this->CheckLineOfSight(position, playerCharacter->GetPosition(), sceneManager->GetTilemap());
				if (aHasLineOfSight == true)//Hat Blickkontakt
				{
					aLastSeen = playerCharacter->GetPosition();
					if (aState == 5)//Greift an
					{
						--aAttackCounter;
						if (aAttackCounter == 0)
						{
							aAttackCounter = aAttackDuration;
							if (CheckCollisionRecs(aAttackArea, playerCharacter->playerHitbox))
							{
								playerCharacter->SetHealth(playerCharacter->GetHealth() - aDamageOutput);
							}
							aState = 0;
						}
					}
					else if (CheckCollisionRecs(aAttackArea, playerCharacter->playerHitbox))//ist in Nahkampfreichweite
					{
						aState = 5;
					}
					else
					{
						aState = 2;
						if (playerCharacter->GetPosition().x < position.x)
						{
							direction = LEFT;
						}
						else
						{
							direction = RIGHT;
						}
					}
					if (aState == 2)	//Nähert sich dem Spieler
					{
						this->Move(direction);
					}
				}
				else
				{
					if (aState == 5 || aState == 2)
					{
						aState = 6;
						aSeekingcounter = aSeekingDuration;
						aAttackCounter = aAttackDuration;
					}
					else if (aState == 6)
					{
						--aSeekingcounter;
						if (aLastSeen.x < position.x)
						{
							direction = LEFT;
						}
						else
						{
							direction = RIGHT;
						}
						if (aSeekingcounter == 0)
						{
							aState = 0;
							aSeekingcounter = aSeekingDuration;
						}
					}
					else if (aState == 0)
					{
						--aIdleWorkCounter;
						if (aIdleWorkCounter == 0)
						{
							aIdleWorkCounter = aIdleWorkDuration;
							aState = 1;
							if (MakeDecision(42))
							{
								if (direction == RIGHT)
								{
									direction = LEFT;
								}
								else
								{
									direction = RIGHT;
								}
							}
						}
					}
					else if (aState == 1)
					{
						--aIdleWorkCounter;
						this->Move(direction);
						if (aIdleWorkCounter == 0)
						{
							aIdleWorkCounter = aIdleWorkDuration;
							aState = 0;
						}
					}
				}
			}
		}
	}
}

void Miner::Draw()
{
	if (CheckCollisionRecs(playerCharacter->visibleScreen, this->aHitbox))
	{
		DrawRectangleRec(aHitbox, YELLOW);
		if (aState == 5)
		{
			DrawRectangleRec(aAttackArea, RED);
		}
		DrawTexture(aTexture, position.x, position.y, WHITE);
	}
}

Miner::~Miner()
{}

void Miner::Move(Direction pDirection)
{
	aEdgeSeekerLeft.x = position.x;
	aEdgeSeekerLeft.y = position.y + 33;
	aEdgeSeekerRight.x = position.x + 32;
	aEdgeSeekerRight.y = position.y + 33;
	sceneManager->GetTilemap();
	Rectangle tileRec = { 0,0,32,32 };
	for (const auto& collTile : tilemap->GetTileColliders())
	{
		tileRec.x = collTile.x;
		tileRec.y = collTile.y;
		if (direction == LEFT && CheckCollisionPointRec(aEdgeSeekerLeft, tileRec))
		{
			position.x -= aMovementSpeed;		//flees to the Left if not on an Edge
			aAttackArea.x = position.x-aAttackArea.width;
			aAttackArea.y = position.y + 12;
		}
		else if (direction == RIGHT && CheckCollisionPointRec(aEdgeSeekerRight, tileRec))
		{
			position.x += aMovementSpeed;		//approaches to the Right if not on an Edge
			aAttackArea.x = position.x+32;
			aAttackArea.y = position.y + 12;
		}
	}
	aHitbox.x = position.x;
	aHitbox - y = position.y;
}
