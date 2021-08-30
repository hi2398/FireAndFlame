#include "TBBeforeFightState.h"
#include "TBIdleState.h"
#include "../../Global.h"
#include "../../Data/TmpDialogueObject.h"

TBBeforeFightState::TBBeforeFightState(Enemy& enemy) : EState(enemy)
{
	pseudoTexture.width = 20 * 32;
	pseudoTexture.height = 20 * 32;
	Vector2 dialogueSpawn = { 49 * 32, 75 * 32 };
	sceneManager->AddInteractable(std::make_unique<TmpDialogueObject>("assets/Dialogues/traitorBossDialogue1.json", dialogueSpawn, pseudoTexture));

	activeFrame = { 0,0,(float)32 * enemy.GetDirection(), 32 };
	activeFrame2 = { 0,0,(float)32 * enemy.GetDirection(), 32 };
}

std::shared_ptr<EState> TBBeforeFightState::Update(Enemy& enemy)
{
	if (IsKeyPressed(KEY_E) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_UP)) textCounter++;
	if (textCounter >= 10) {
		sceneManager->GetInteractables().back()->MarkToDestroy();
		return std::make_shared<TBIdleState>(enemy);
	}

	stateFrameCounter++;
	if (stateFrameCounter >= 15) {
		stateFrameCounter = 0;
		thisFrame++;
		thisFrame2++;
	}

	activeFrame = { (float)32 * thisFrame, 0, (float)32 * enemy.GetDirection(), 32 };
	activeFrame2 = { (float)32 * thisFrame2, 0, (float)32 * enemy.GetDirection(), 32 };

	if (!enemy.IsGrounded()) {
		enemy.SetPosition({enemy.GetPosition().x, enemy.GetPosition().y + 5.0f});
		activeFrame.y = (float)32 * 5;
		activeFrame2.y = (float)32 * 2;
	}

	return shared_from_this();
}

void TBBeforeFightState::Draw(Enemy& enemy)
{
	DrawTextureRec(enemy.GetSecondTexture(), activeFrame2, enemy.GetPosition(), WHITE);
	DrawTextureRec(enemy.GetTexture(), activeFrame, enemy.GetPosition(), WHITE);
}
