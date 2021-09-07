#include "IdleState.h"
#include "../../Core/Enemy.h"
#include "../../../src/Global.h"
#include "ApproachingState.h"
#include "AttackingState.h"
#include "RoamingState.h"
#include "StunnedState.h"

#include "raymath.h"

ApproachingState::ApproachingState(Enemy& enemy) : EState(enemy)
{
	switch (enemy.GetEnemyType())
	{
	case EnemyTypes::ToastCat:
		activeFrame = { (float)32 * thisFrame, 32 * 5, (float)-32 * enemy.GetDirection(), 32 };
		break;
	case EnemyTypes::SpiderBot:
		activeFrame = { 0,32 * 4,(float)-32 * enemy.GetDirection(), 32 };
		//normal walking
		if (enemy.IsGrounded() && !enemy.GetHeadCollision() && !enemy.GetWallCollisionLeft() && !enemy.GetWallCollisionRight()) {
			spiderBotRotation = 0;
		}
		//walk on ceiling
		else if (enemy.GetHeadCollision()) {
			spiderBotRotation = 180;
		}
		if (enemy.GetHeadCollision() && enemy.GetWallCollisionLeft() && enemy.GetDirection() == RIGHT) {
			spiderBotRotation = 90;
		}
		if (enemy.GetHeadCollision() && enemy.GetWallCollisionRight() && enemy.GetDirection() == LEFT) {
			spiderBotRotation = 270;
		}

		//walk up/down left wall
		if (enemy.GetWallCollisionLeft()) {
			spiderBotRotation = 90;
		}
		if (enemy.GetWallCollisionLeft() && enemy.IsGrounded() && enemy.GetDirection() == RIGHT) {
			spiderBotRotation = 0;
		}

		//walk up/down left wall
		if (enemy.GetWallCollisionRight()) {
			spiderBotRotation = 270;
		}
		if (enemy.GetWallCollisionRight() && enemy.IsGrounded() && enemy.GetDirection() == LEFT) {
			spiderBotRotation = 0;
		}
		break;
	case EnemyTypes::SpringHog:
		activeFrame = { 32, 32 * 3, (float) 32 * enemy.GetDirection(), 32};
		break;
	case EnemyTypes::Saugi:
		heart = std::make_unique<HeartObject>(enemy.GetPosition(), HeartState::Good, 2);
	default:
		activeFrame.y = 32 * 4;
		break;
	}
}

std::shared_ptr<EState> ApproachingState::Update(Enemy& enemy)
{

	if constexpr (DEBUG_ENEMY_STATES) {
		std::cout << "Enemy State: Approaching\n";
	}
	//frameCounter for animation
	stateFrameCounter++;
	//frame handling
	if (stateFrameCounter >= 15) {
		thisFrame++;
		stateFrameCounter = 0;
	}
	activeFrame = {(float) 32 * thisFrame, 32 * 4, (float) -32 * enemy.GetDirection(), 32};
	

	Rectangle enemySight;
	//Vector points for triangle sight
	trianglePoint1 = { enemy.GetPosition().x + (32 * 5 * enemy.GetDirection()), enemy.GetPosition().y - 32 * 3 };
	trianglePoint2 = { enemy.GetPosition().x + (32 * 5 * enemy.GetDirection()), enemy.GetPosition().y + 32 * 4 };

	switch (enemy.GetEnemyType())
	{
	case EnemyTypes::Saugi:
		heart->Update();
		heart->UpdatePos(enemy.GetPosition());
		for (const auto& coal : sceneManager->GetInteractables()) {
			//check line of sight in idle
			enemySight = { enemy.GetPosition().x + 16 - 16 * 32, enemy.GetPosition().y + 16, 16 * 32, 5 };;
			if (CheckCollisionRecs(coal->GetInteractionZone(), enemySight) && coal->GetInteractableType() == InteractableType::Coal) {
				enemy.SetDirection(LEFT);
			}

			enemySight = { enemy.GetPosition().x + 16, enemy.GetPosition().y + 16, 16 * 32, 5 };;
			if (CheckCollisionRecs(coal->GetInteractionZone(), enemySight) && coal->GetInteractableType() == InteractableType::Coal) {
				enemy.SetDirection(RIGHT);
			}
			
			enemy.SetPosition({ enemy.GetPosition().x + enemy.GetEnemyMovementSpeed() * enemy.GetDirection(), enemy.GetPosition().y });

			if (CheckCollisionRecs(coal->GetInteractionZone(), enemy.GetCollider()) && coal->GetInteractableType() == InteractableType::Coal) {
				coal->Interact(enemy);
				return std::make_shared<RoamingState>(enemy);
			}

			if (CheckCollisionRecs(coal->GetInteractionZone(), playerCharacter->playerHitbox) && coal->GetInteractableType() == InteractableType::Coal) {
				return std::make_shared<StunnedState>(enemy);
			}
		}
		aggroCooldown++;

		if (aggroCooldown >= 240) {
			return std::make_shared<StunnedState>(enemy);
		}
		break;
	case EnemyTypes::SpringHog:
		//set springhog direction to player direction
		playerReference = Vector2Subtract(playerCharacter->GetPosition(), enemy.GetPosition());
		if (playerReference.x > 0) {

			enemy.SetDirection(RIGHT);
		}
		else {

			enemy.SetDirection(LEFT);
		}
		activeFrame = { 32, 32 * 3, (float)32 * enemy.GetDirection(), 32 };
		//springhog sight
		if (enemy.IsGrounded()) {
			if (CheckCollisionPointCircle(playerCharacter->GetPosition(), { enemy.GetPosition().x + 16, enemy.GetPosition().y + 16}, 32 * 4)) {
				return std::make_shared<AttackingState>(enemy);
			}
			else return std::make_shared<RoamingState>(enemy);
		}
		break;
	case EnemyTypes::SpiderBot:
		aggroCooldown++;
		if (aggroCooldown >= 290) {
			return std::make_shared<AttackingState>(enemy);
		}
		if (thisFrame >= 2) thisFrame = 0;
		activeFrame = { (float)32 * thisFrame, 32 * 4 ,(float)-32 * enemy.GetDirection(), 32 };

		approachingSpeed = enemy.GetEnemyMovementSpeed() * 1;

		//handle enemy direction
		if (!CheckCollisionPointCircle(playerCharacter->GetPosition(), { enemy.GetPosition().x + 16, enemy.GetPosition().y + 16 }, 32 * 4)) {
			return std::make_shared<AttackingState>(enemy);
		}
		else {
			playerReference = Vector2Subtract(playerCharacter->GetPosition(), enemy.GetPosition());
			movingToPlayer = Vector2Normalize(playerReference);
			if (playerReference.y >= 0) {
				if (spiderBotRotation == 270) {
					enemy.SetDirection(RIGHT);
				}
				else if (spiderBotRotation == 90) {
					enemy.SetDirection(LEFT);
				}
				else if (spiderBotRotation == 180) {
					if (playerReference.x > 5) {
						enemy.SetDirection(LEFT);

					}
					else if (playerReference.x < -5) {
						enemy.SetDirection(RIGHT);

					}
				}
				else if (playerReference.x > approachingSpeed*2) {
					enemy.SetDirection(LEFT);

				}
				else if (playerReference.x < -approachingSpeed*2) {
					enemy.SetDirection(RIGHT);

				}
			}
		}
		//normal walking
		if (enemy.IsGrounded() && !enemy.GetHeadCollision() && !enemy.GetWallCollisionLeft() && !enemy.GetWallCollisionRight()) {
			spiderBotRotation = 0;
			enemy.SetPosition({ enemy.GetPosition().x + approachingSpeed * enemy.GetDirection(), enemy.GetPosition().y });
		}
		//walk on ceiling
		if (enemy.GetHeadCollision()) {
			spiderBotRotation = 180;
			enemy.SetPosition({ enemy.GetPosition().x - approachingSpeed * enemy.GetDirection(), enemy.GetPosition().y });
		}
		if (enemy.GetHeadCollision() && enemy.GetWallCollisionLeft() && enemy.GetDirection() == RIGHT) {
			spiderBotRotation = 90;
			enemy.SetPosition({ enemy.GetPosition().x, enemy.GetPosition().y + approachingSpeed * enemy.GetDirection() });
		}
		if (enemy.GetHeadCollision() && enemy.GetWallCollisionRight() && enemy.GetDirection() == LEFT) {
			spiderBotRotation = 270;
			enemy.SetPosition({ enemy.GetPosition().x, enemy.GetPosition().y - approachingSpeed * enemy.GetDirection() });
		}


		//walk up/down left wall
		if (enemy.GetWallCollisionLeft()) {
			spiderBotRotation = 90;
			enemy.SetPosition({ enemy.GetPosition().x, enemy.GetPosition().y + approachingSpeed * enemy.GetDirection() });

		}
		if (enemy.GetWallCollisionLeft() && enemy.IsGrounded() && enemy.GetDirection() == RIGHT) {
			spiderBotRotation = 0;
			enemy.SetPosition({ enemy.GetPosition().x + approachingSpeed * enemy.GetDirection(), enemy.GetPosition().y });
		}

		//walk up/down left wall
		if (enemy.GetWallCollisionRight()) {
			spiderBotRotation = 270;
			enemy.SetPosition({ enemy.GetPosition().x, enemy.GetPosition().y - approachingSpeed * enemy.GetDirection() });

		}
		if (enemy.GetWallCollisionRight() && enemy.IsGrounded() && enemy.GetDirection() == LEFT) {
			spiderBotRotation = 0;
			enemy.SetPosition({ enemy.GetPosition().x + approachingSpeed * enemy.GetDirection(), enemy.GetPosition().y });
		}

		if (enemy.GetHeadCollision() && enemy.IsGrounded()) {
			spiderBotRotation = 0;
			enemy.SetPosition({ enemy.GetPosition().x + approachingSpeed * enemy.GetDirection(), enemy.GetPosition().y });
		}

		break;
	case EnemyTypes::Flyer:
		//enter attack after some time or when in range
		if (flyApproachingCounter >= 180) {
			return std::make_shared<AttackingState>(enemy);
		}

		flyApproachingCounter++;
		if (stateFrameCounter >= 15) {
			thisFrame++;
			stateFrameCounter = 0;
		}
		if (thisFrame >= 3) thisFrame = 0;
		activeFrame = { (float)32 * thisFrame, 32 * 5, (float)-32 * enemy.GetDirection(), 32 };

		playerReference = Vector2Subtract(playerCharacter->GetPosition(), enemy.GetPosition());
		movingToPlayer = Vector2Normalize(playerReference);
		if (playerReference.x > 0) {
			
			enemy.SetDirection(RIGHT);
		}
		else {
			
			enemy.SetDirection(LEFT);
		}
		if (playerReference.y >=  5) enemy.SetPosition({ enemy.GetPosition().x + movingToPlayer.x, enemy.GetPosition().y + movingToPlayer.y});
		else enemy.SetPosition({ enemy.GetPosition().x + movingToPlayer.x, enemy.GetPosition().y - 1.0f});

		//aggro check
		if (CheckCollisionPointCircle(playerCharacter->GetPosition(),
			{ enemy.GetPosition().x + 16, enemy.GetPosition().y + 16 },
			5 * 32)) {
			aggroCooldown = 0;
		}
		else {
			aggroCooldown++;
		}

		break;
	case EnemyTypes::ToastCat:
		//check line of sight in approaching
		if (CheckCollisionPointTriangle(playerCharacter->GetPosition(),
			{ enemy.GetPosition().x + 16, enemy.GetPosition().y + 16}, 
			trianglePoint1, 
			trianglePoint2) ||
			CheckCollisionRecs(playerCharacter->playerHitbox, { enemy.GetPosition().x + 16, enemy.GetPosition().y, 32, 32 })) {
			return std::make_shared<AttackingState>(enemy);
		}
		return std::make_shared<RoamingState>(enemy);
		break;
	case EnemyTypes::Howler:
		if (enemy.GetJumpCommand() || !enemy.IsGrounded()) {
			thisFrame = 1;
			activeFrame = { (float)32 * thisFrame, 32 * 2 ,(float)-32 * enemy.GetDirection(), 32 };
		}
		else {
			activeFrame = { (float)32 * thisFrame, 32 * 1 ,(float)-32 * enemy.GetDirection(), 32 };
		}

		//chase Player & stop on ledge
		edgeSeekerLeft = { enemy.GetPosition().x - 1, enemy.GetPosition().y + 32, 1, 1 };
		edgeSeekerRight = { enemy.GetPosition().x + 32, enemy.GetPosition().y + 32, 1, 1 };
		
		movingToPlayer = Vector2Subtract(playerCharacter->GetPosition(), enemy.GetPosition());
		if (movingToPlayer.x > 0 && !enemy.GetJumpCommand()) movingDistance = enemy.GetEnemyMovementSpeed() * 1.5f, enemy.SetDirection(RIGHT);
		else if (movingToPlayer.x < 0 && !enemy.GetJumpCommand()) movingDistance = -enemy.GetEnemyMovementSpeed() * 1.5f, enemy.SetDirection(LEFT);
			
		for (const auto& collTile : sceneManager->GetTilemap()->GetTileColliders())
		{
			tileRec.x = collTile.x;
			tileRec.y = collTile.y;

			
			if (CheckCollisionRecs(edgeSeekerLeft, tileRec)) {
				collCheckLeft++;
			}
			if (CheckCollisionRecs(edgeSeekerRight, tileRec)) {
				collCheckRight++;
			}
			


		}

		//jump over ledge
		if (collCheckLeft == 0 && enemy.IsGrounded() || enemy.GetJumpCommand()) {
			enemy.SetJumpCommand(true);
			enemy.SetPosition({ enemy.GetPosition().x + enemy.GetEnemyMovementSpeed() * 3 * enemy.GetDirection(), enemy.GetPosition().y - enemy.GetJumpSpeed() });
			enemy.SetJumpSpeed(enemy.GetJumpSpeed()- 0.2f);
		}
		else if (collCheckRight == 0 && enemy.IsGrounded() || enemy.GetJumpCommand()) {
			enemy.SetJumpCommand(true);
			enemy.SetPosition({ enemy.GetPosition().x + enemy.GetEnemyMovementSpeed() * 3 * enemy.GetDirection(), enemy.GetPosition().y - enemy.GetJumpSpeed() });
			enemy.SetJumpSpeed(enemy.GetJumpSpeed() - 0.2f);
		}
		else {//or just move normally
			if (movingToPlayer.x <= 16 && movingToPlayer.x >= -16) {
				if (thisFrame >= 2) thisFrame = 0;
				activeFrame.y = 0;
			}
			else {
				if (enemy.IsGrounded()) enemy.SetPosition({ enemy.GetPosition().x + movingDistance * 2, enemy.GetPosition().y });
			}
			
		}

		//check sight detection in certain radius
		if (CheckCollisionPointCircle(playerCharacter->GetPosition(),
			{ enemy.GetPosition().x + 16, enemy.GetPosition().y + 16 },
			3 * 32) && enemy.IsGrounded()) {
			return std::make_shared<AttackingState>(enemy);
		}

		//aggro check
		if (CheckCollisionPointCircle(playerCharacter->GetPosition(),
			{ enemy.GetPosition().x + 16, enemy.GetPosition().y + 16 },
			5 * 32) && enemy.IsGrounded()) {
			aggroCooldown = 0;
		}
		else {
			aggroCooldown++;
		}
		

		break;
	default:
			

		//check line of sight in approaching
		switch (enemy.GetDirection())
		{
		case LEFT:
			enemySight = { enemy.GetPosition().x + 16 - 160, enemy.GetPosition().y + 16, 160, 5 };
			if (CheckCollisionRecs(playerCharacter->playerHitbox, enemySight)) {
				aggroCooldown = 0;
			}
			else {
				aggroCooldown++;
			}
			break;
		case RIGHT:
			enemySight = { enemy.GetPosition().x + 16, enemy.GetPosition().y + 16, 160, 5 };
			if (CheckCollisionRecs(playerCharacter->playerHitbox, enemySight)) {
				aggroCooldown = 0;
			}
			else {
				aggroCooldown++;
			}
			break;
		default:
			break;
		}
		
		//chase Player & stop on ledge
		edgeSeekerLeft = { enemy.GetPosition().x - 1, enemy.GetPosition().y + 32, 1, 1 };
		edgeSeekerRight = { enemy.GetPosition().x + 32, enemy.GetPosition().y + 32, 1, 1 };
		for (const auto& collTile : sceneManager->GetTilemap()->GetTileColliders())
		{
			tileRec.x = collTile.x;
			tileRec.y = collTile.y;

			movingToPlayer = Vector2Subtract(playerCharacter->GetPosition(), enemy.GetPosition());
			if (movingToPlayer.x > 0) movingDistance = enemy.GetEnemyMovementSpeed()*1.5f, enemy.SetDirection(RIGHT);
			else if (movingToPlayer.x < 0) movingDistance = -enemy.GetEnemyMovementSpeed()*1.5f, enemy.SetDirection(LEFT);

			//stop follow player over ledge
			if ((CheckCollisionRecs(edgeSeekerLeft, tileRec) && enemy.GetDirection() == LEFT) || (CheckCollisionRecs(edgeSeekerRight, tileRec) && enemy.GetDirection() == RIGHT)) {
				enemy.SetPosition({ enemy.GetPosition().x + movingDistance, enemy.GetPosition().y });
			}
			
		}


		

		//enter attacking state when in range
		if (CheckCollisionRecs(playerCharacter->playerHitbox, enemy.GetAttackHitbox())) {
			return std::make_shared<AttackingState>(enemy);
		}

		break;
	}
	//enter idle when losing aggro after 5 secs
	if (aggroCooldown >= 300 && enemy.GetEnemyType() != EnemyTypes::Saugi) {
		if (enemy.GetEnemyType() == EnemyTypes::Howler) {
			if (enemy.IsGrounded()) return std::make_shared<RoamingState>(enemy);
		}
		else {
			return std::make_shared<RoamingState>(enemy);
		}
		
	}

	if (enemy.IsInvulnerable()) {
		return std::make_shared<StunnedState>(enemy);
	}

	collCheckLeft = 0;
	collCheckRight = 0;
	return shared_from_this();
}

void ApproachingState::Draw(Enemy& enemy)
{
	if (enemy.GetEnemyType() == EnemyTypes::SpiderBot) {
		DrawTexturePro(enemy.GetTexture(), activeFrame, { enemy.GetPosition().x + 16, enemy.GetPosition().y + 16, 32, 32 }, { 16, 16 }, spiderBotRotation, WHITE);
	}
	else {
		DrawTextureRec(enemy.GetTexture(), activeFrame, { enemy.GetPosition().x, enemy.GetPosition().y }, WHITE);
	}

	if (enemy.GetEnemyType() == EnemyTypes::Saugi) {
		heart->Draw();
	}
}
