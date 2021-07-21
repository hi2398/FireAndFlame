#include "Miner.h"
#include "../../Global.h"
#include "EnemyStateHandler.h"

Miner::Miner(Vector2 initialPos): Enemy(EnemyTypes::Miner)
{
	texture = LoadTexture("assets/graphics/Enemies/Miner.png");
	position.x = initialPos.x;
	position.y = initialPos.y;
	hitbox.x = initialPos.x;
	hitbox.y = initialPos.y;
	hitbox.width = 32;
	hitbox.height = 32;
	movementSpeed = 1.0f;
	activeState = std::make_shared<EnemyStateHandler>(*this);

    /*stunCounter = stunDuration;
    attackCounter = attackDuration;
    seekingCounter = seekingDuration;
	idleWorkCounter = idleWorkDuration;
    attackArea.height = 15;
    attackArea.width = 26;
	

	*/
}

//void Miner::Update()
//{
//	aOnScreen = this->CheckOnScreen();
//	if (aOnScreen)//Wird Gerendert
//	{
//		if (grounded)//ist auf dem Boden
//		{
//			fallingSpeed = 0.f;
//			if (state == EnemyState::Stunned)//Ist gestunned
//			{
//				--stunCounter;
//				if (stunCounter == 0)
//				{
//                    stunCounter = stunDuration;
//                    state = EnemyState::Idle;
//				}
//			}
//			else//Ist nicht gestunned
//			{
//				//std::cout << "not stunned";
//                
//				if (hasLineOfSight)//Hat Blickkontakt
//				{
//                    lastSeen = playerCharacter->GetPosition();
//					if (state == EnemyState::Attacking)//Greift an
//					{
//						--attackCounter;
//						if (attackCounter == 0)
//						{
//                            attackCounter = attackDuration;
//							if (CheckCollisionRecs(attackArea, playerCharacter->playerHitbox))
//							{
//								playerCharacter->SetHealth(playerCharacter->GetHealth() - aDamageOutput);
//							}
//                            state = EnemyState::Idle;
//						}
//					}
//					else if (CheckCollisionRecs(attackArea, playerCharacter->playerHitbox))//ist in Nahkampfreichweite
//					{
//                        state = EnemyState::Attacking;
//					}
//					else
//					{
//						if (lastSeen.x < position.x)
//						{
//							direction = LEFT;
//						}
//						else
//						{
//							direction = RIGHT;
//						}
//						state = EnemyState::Approaching;
//					}
//					if (state == EnemyState::Approaching)	//Nähert sich dem Spieler
//					{
//						this->Move(direction);
//					}
//				}
//				else
//				{
//					if (state == EnemyState::Attacking || state == EnemyState::Approaching)
//					{
//                        state = EnemyState::Seeking;
//                        seekingCounter = seekingDuration;
//                        attackCounter = attackDuration;
//					}
//					else if (state == EnemyState::Seeking)
//					{
//						--seekingCounter;
//						if (lastSeen.x < position.x)
//						{
//							direction = LEFT;
//						}
//						else
//						{
//							direction = RIGHT;
//						}
//						if (seekingCounter == 0)
//						{
//                            state = EnemyState::Idle;
//                            seekingCounter = seekingDuration;
//						}
//					}
//					else if (state == EnemyState::Idle)
//					{
//						std::cout << "Miner Idle\n";
//						--idleWorkCounter;
//						if (idleWorkCounter == 0)
//						{
//                            idleWorkCounter = idleWorkDuration;
//                            state = EnemyState::Roaming;
//							if (MakeDecision(30))
//							{
//								if (direction == RIGHT)
//								{
//									direction = LEFT;
//								}
//								else
//								{
//									direction = RIGHT;
//								}
//							}
//						}
//					}
//					else if (state == EnemyState::Roaming)
//					{
//						std::cout << "Miner Roaming\n";
//						--idleWorkCounter;
//						this->Move(direction);
//						if (idleWorkCounter == 0)
//						{
//                            idleWorkCounter = idleWorkDuration;
//                            state = EnemyState::Idle;
//						}
//					}
//				}
//			}
//		}
//		else
//		{
//			this->position.y += fallingSpeed;
//			fallingSpeed += 0.1f;
//			hitbox.x = position.x;
//			hitbox.y = position.y;
//			Rectangle tileRec = { 0,0,32,32 };
//			for (const auto& collTile : sceneManager->GetTilemap()->GetTileColliders())
//			{
//				tileRec.x = collTile.x;
//				tileRec.y = collTile.y;
//				if (CheckCollisionRecs(hitbox, tileRec))
//				{
//					grounded = true;
//				}
//			}
//		}
//	}
//}

void Miner::Update() {
	activeState = activeState->Update(*this);

	UpdateAttackHitbox();
	UpdateCollider();

	if (invulnerable) {
		invulnerableCounter++;
		if (invulnerableCounter >= 60) {
			invulnerableCounter = 0;
			invulnerable = false;
		}
	}

	if (!IsGrounded()) position.y += 2.0f;
	CollisionLeft(sceneManager->GetTilemap());
	CollisionRight(sceneManager->GetTilemap());
	CollisionGround(sceneManager->GetTilemap());
	CollisionHead(sceneManager->GetTilemap());
}

void Miner::Draw()
{
	activeState->Draw(*this);
	DrawText(TextFormat("%i", health), position.x, position.y-50, 30, WHITE);
	/*if (CheckCollisionRecs(playerCharacter->visibleScreen, this->hitbox))
	{
		if (state == EnemyState::Attacking)
		{
			DrawRectangleRec(attackArea, RED);
		}
		DrawTexture(texture, position.x, position.y, WHITE);
	}*/
}

//
//void Miner::Move(Direction pDirection)
//{
//	aEdgeSeekerLeft.x = position.x;
//	aEdgeSeekerLeft.y = position.y + 33;
//	aEdgeSeekerRight.x = position.x + 32;
//	aEdgeSeekerRight.y = position.y + 33;
//	Rectangle tileRec = { 0,0,32,32 };
//	for (const auto& collTile : sceneManager->GetTilemap()->GetTileColliders())
//	{
//		tileRec.x = collTile.x;
//		tileRec.y = collTile.y;
//		if (direction == LEFT && CheckCollisionPointRec(aEdgeSeekerLeft, tileRec))
//		{
//			position.x -= aMovementSpeed;		//flees to the Left if not on an Edge
//			attackArea.x = position.x - attackArea.width;
//            attackArea.y = position.y + 12;
//			aWallSeekerLeft.x = position.x - 1;
//			aWallSeekerLeft.y = position.y + 16;
//		}
//		else if (direction == RIGHT && CheckCollisionPointRec(aEdgeSeekerRight, tileRec))
//		{
//			position.x += aMovementSpeed;		//approaches to the Right if not on an Edge
//			attackArea.x = position.x + 32;
//            attackArea.y = position.y + 12;
//			aWallSeekerRight.x = position.x + 33;
//			aWallSeekerRight.y = position.y + 16;
//		}
//		if (direction == RIGHT && CheckCollisionPointRec(aWallSeekerRight, tileRec))
//		{
//			direction = LEFT;
//		}
//		else if (direction == LEFT && CheckCollisionPointRec(aWallSeekerLeft, tileRec))
//		{
//			direction = RIGHT;
//		}
//	}
//	hitbox.x = position.x;
//	hitbox.y = position.y;
//}
