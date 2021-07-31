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
	case EnemyTypes::ToastCat:
		//check line of sight in approaching
		if (CheckCollisionPointTriangle(playerCharacter->GetPosition(),
			{ enemy.GetPosition().x + 16, enemy.GetPosition().y + 16}, 
			trianglePoint1, 
			trianglePoint2)) {
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
		if (movingToPlayer.x > 0 && !enemy.GetJumpCommand()) movingDistance = enemy.GetEnemyMovementSpeed() * 1.5, enemy.SetDirection(RIGHT);
		else if (movingToPlayer.x < 0 && !enemy.GetJumpCommand()) movingDistance = -enemy.GetEnemyMovementSpeed() * 1.5, enemy.SetDirection(LEFT);
			
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
			enemySight = { enemy.GetPosition().x + enemy.GetTexture().width / 2 - 160, enemy.GetPosition().y + enemy.GetTexture().height / 2, 160, 5 };
			if (CheckCollisionRecs(playerCharacter->playerHitbox, enemySight)) {
				aggroCooldown = 0;
			}
			else {
				aggroCooldown++;
			}
			break;
		case RIGHT:
			enemySight = { enemy.GetPosition().x + enemy.GetTexture().width / 2, enemy.GetPosition().y + enemy.GetTexture().height / 2, 160, 5 };
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

			Vector2 movingToPlayer;
			movingToPlayer = Vector2Subtract(playerCharacter->GetPosition(), enemy.GetPosition());
			if (movingToPlayer.x > 0) movingDistance = enemy.GetEnemyMovementSpeed()*1.5, enemy.SetDirection(RIGHT);
			else if (movingToPlayer.x < 0) movingDistance = -enemy.GetEnemyMovementSpeed()*1.5, enemy.SetDirection(LEFT);

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
	if (aggroCooldown >= 300) {
		return std::make_shared<RoamingState>(enemy);
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
	DrawTextureRec(enemy.GetTexture(), activeFrame, { enemy.GetPosition().x, enemy.GetPosition().y }, WHITE);
}
