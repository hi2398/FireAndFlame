#include "Miner.h"
#include "../Global.h"

Miner::Miner(Vector2 initialPos): Enemy(EnemyTypes::Miner)
{
    texture = LoadTexture("assets/graphics/Enemies/Miner.png");
	position.x = initialPos.x;
	position.y = initialPos.y;
    hitbox.x = initialPos.x;
    hitbox.y = initialPos.y;
    hitbox.width = 32;
    hitbox.height = 32;
    stunCounter = stunDuration;
    attackCounter = attackDuration;
    seekingCounter = seekingDuration;
    attackArea.height = 15;
    attackArea.width = 26;
}

void Miner::Update()
{
	aOnScreen = this->CheckOnScreen();
	if (aOnScreen == true)//Wird Gerendert
	{
		if (grounded == true)//ist auf dem Boden
		{
			fallingSpeed = 0.f;
			if (state == 4)//Ist gestunned
			{
				--stunCounter;
				if (stunCounter == 0)
				{
                    stunCounter = stunDuration;
                    state = 0;
				}
			}
			else//Ist nicht gestunned
			{

                hasLineOfSight = this->CheckLineOfSight(position, playerCharacter->GetPosition(), sceneManager->GetTilemap());
				if (hasLineOfSight == true)//Hat Blickkontakt
				{
                    lastSeen = playerCharacter->GetPosition();
					if (state == 5)//Greift an
					{
						--attackCounter;
						if (attackCounter == 0)
						{
                            attackCounter = attackDuration;
							if (CheckCollisionRecs(attackArea, playerCharacter->playerHitbox))
							{
								playerCharacter->SetHealth(playerCharacter->GetHealth() - aDamageOutput);
							}
                            state = 0;
						}
					}
					else if (CheckCollisionRecs(attackArea, playerCharacter->playerHitbox))//ist in Nahkampfreichweite
					{
                        state = 5;
					}
					else
					{
                        state = 2;
						if (playerCharacter->GetPosition().x < position.x)
						{
							direction = LEFT;
						}
						else
						{
							direction = RIGHT;
						}
					}
					if (state == 2)	//Nähert sich dem Spieler
					{
						this->Move(direction);
					}
				}
				else
				{
					if (state == 5 || state == 2)
					{
                        state = 6;
                        seekingCounter = seekingDuration;
                        attackCounter = attackDuration;
					}
					else if (state == 6)
					{
						--seekingCounter;
						if (lastSeen.x < position.x)
						{
							direction = LEFT;
						}
						else
						{
							direction = RIGHT;
						}
						if (seekingCounter == 0)
						{
                            state = 0;
                            seekingCounter = seekingDuration;
						}
					}
					else if (state == 0)
					{
						--idleWorkCounter;
						if (idleWorkCounter == 0)
						{
                            idleWorkCounter = idleWorkDuration;
                            state = 1;
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
					else if (state == 1)
					{
						--idleWorkCounter;
						this->Move(direction);
						if (idleWorkCounter == 0)
						{
                            idleWorkCounter = idleWorkDuration;
                            state = 0;
						}
					}
				}
			}
		}
		else
		{
			this->position.y += fallingSpeed;
			fallingSpeed += 0.1f;
		}
	}
}

void Miner::Draw()
{
	if (CheckCollisionRecs(playerCharacter->visibleScreen, this->hitbox))
	{
		DrawRectangleRec(hitbox, YELLOW);
		if (state == 5)
		{
			DrawRectangleRec(attackArea, RED);
		}
		DrawTexture(texture, position.x, position.y, WHITE);
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
	Rectangle tileRec = { 0,0,32,32 };
	for (const auto& collTile : sceneManager->GetTilemap()->GetTileColliders())
	{
		tileRec.x = collTile.x;
		tileRec.y = collTile.y;
		if (direction == LEFT && CheckCollisionPointRec(aEdgeSeekerLeft, tileRec))
		{
			position.x -= aMovementSpeed;		//flees to the Left if not on an Edge
			attackArea.x = position.x - attackArea.width;
            attackArea.y = position.y + 12;
		}
		else if (direction == RIGHT && CheckCollisionPointRec(aEdgeSeekerRight, tileRec))
		{
			position.x += aMovementSpeed;		//approaches to the Right if not on an Edge
			attackArea.x = position.x + 32;
            attackArea.y = position.y + 12;
		}
	}
    hitbox.x = position.x;
    hitbox.y = position.y;
}
