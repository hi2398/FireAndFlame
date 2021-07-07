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
	if (aOnScreen)//Wird Gerendert
	{
		if (grounded)//ist auf dem Boden
		{
			fallingSpeed = 0.f;
			if (state == EnemyState::Stunned)//Ist gestunned
			{
				--stunCounter;
				if (stunCounter == 0)
				{
                    stunCounter = stunDuration;
                    state = EnemyState::Idle;
				}
			}
			else//Ist nicht gestunned
			{

                hasLineOfSight = this->CheckLineOfSight(position, playerCharacter->GetPosition(), sceneManager->GetTilemap());
				if (hasLineOfSight)//Hat Blickkontakt
				{
                    lastSeen = playerCharacter->GetPosition();
					if (state == EnemyState::Attacking)//Greift an
					{
						--attackCounter;
						if (attackCounter == 0)
						{
                            attackCounter = attackDuration;
							if (CheckCollisionRecs(attackArea, playerCharacter->playerHitbox))
							{
								playerCharacter->SetHealth(playerCharacter->GetHealth() - aDamageOutput);
							}
                            state = EnemyState::Idle;
						}
					}
					else if (CheckCollisionRecs(attackArea, playerCharacter->playerHitbox))//ist in Nahkampfreichweite
					{
                        state = EnemyState::Attacking;
					}
					else
					{
                        state = EnemyState::Approaching;
						if (playerCharacter->GetPosition().x < position.x)
						{
							direction = LEFT;
						}
						else
						{
							direction = RIGHT;
						}
					}
					if (state == EnemyState::Approaching)	//Nähert sich dem Spieler
					{
						this->Move(direction);
					}
				}
				else
				{
					if (state == EnemyState::Attacking || state == EnemyState::Approaching)
					{
                        state = EnemyState::Seeking;
                        seekingCounter = seekingDuration;
                        attackCounter = attackDuration;
					}
					else if (state == EnemyState::Seeking)
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
                            state = EnemyState::Idle;
                            seekingCounter = seekingDuration;
						}
					}
					else if (state == EnemyState::Idle)
					{
						--idleWorkCounter;
						if (idleWorkCounter == 0)
						{
                            idleWorkCounter = idleWorkDuration;
                            state = EnemyState::Roaming;
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
					else if (state == EnemyState::Roaming)
					{
						--idleWorkCounter;
						this->Move(direction);
						if (idleWorkCounter == 0)
						{
                            idleWorkCounter = idleWorkDuration;
                            state = EnemyState::Idle;
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
		if (state == EnemyState::Attacking)
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
