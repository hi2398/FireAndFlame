#include "TBAfterFightState.h"
#include "../../Global.h"
#include "../../Data/TmpDialogueObject.h"
#include "raymath.h"

TBAfterFightState::TBAfterFightState(Enemy& enemy) : EState(enemy)
{
	if constexpr (DEBUG_ENEMY_STATES) std::cout << "TBSeekCoal\n";
	pseudoTexture.width = 20 * 32;
	pseudoTexture.height = 20 * 32;
	dialogueSpawn = { 49 * 32, 75 * 32 };
	interactField = { enemy.GetPosition().x - 20, enemy.GetPosition().y, 72, 32 };

	
	speechbubble = std::make_unique<Speechbubble>(enemy.GetPosition());

	direction = enemy.GetDirection();
	activeFrame = { 0,0,(float)32 * enemy.GetDirection(), 32 };
	activeFrame2 = { 0,0,(float)32 * enemy.GetDirection(), 32 };

	Vector2 playerReference = Vector2Subtract(playerCharacter->GetPosition(), enemy.GetPosition());
	if (playerReference.x >= 0) {
		enemy.SetDirection(RIGHT);
	}
	else enemy.SetDirection(LEFT);
}

std::shared_ptr<EState> TBAfterFightState::Update(Enemy& enemy)
{
	speechbubble->Update();
	if (CheckCollisionRecs(playerCharacter->playerHitbox, interactField) && !endingText) {
		if (IsKeyPressed(KEY_E) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_UP)) {
			sceneManager->AddInteractable(std::make_unique<TmpDialogueObject>("assets/Dialogues/traitorBossDialogue2.json", dialogueSpawn, pseudoTexture));
			endingText = true;
			speechbubble->MarkToDestroy();
		}
	}


	if (endingText) {
		if (IsKeyPressed(KEY_E) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_UP)) textCounter++;
		if (textCounter >= 14) {
			sceneManager->GetInteractables().back()->MarkToDestroy();
			enemy.MarkToDestroy();
		}
	}
	

	stateFrameCounter++;
	if (stateFrameCounter >= 15) {
		stateFrameCounter = 0;
		thisFrame++;
		thisFrame2++;
	}

	activeFrame = { (float)32 * thisFrame, 0, (float)32 * direction, 32 };
	activeFrame2 = { (float)32 * thisFrame2, 0, (float)32 * direction, 32 };

	return shared_from_this();
}

void TBAfterFightState::Draw(Enemy& enemy)
{
	DrawTextureRec(enemy.GetSecondTexture(), activeFrame2, enemy.GetPosition(), WHITE);
	DrawTextureRec(enemy.GetTexture(), activeFrame, enemy.GetPosition(), WHITE);

	if (!endingText) {
	speechbubble->Draw();
	}
}
