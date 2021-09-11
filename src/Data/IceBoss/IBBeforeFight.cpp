#include "IBBeforeFight.h"
#include "../../Global.h"
#include "../../Data/TmpDialogueObject.h"
#include "IceBoss.h"
#include "IBSeek.h"

IBBeforeFight::IBBeforeFight(Enemy& enemy) : EState(enemy)
{
	pseudoTexture.width = 20 * 32;
	pseudoTexture.height = 20 * 32;
	Vector2 dialogueSpawn = { 21 * 32, 27 * 32 };
	sceneManager->AddInteractable(std::make_unique<TmpDialogueObject>("assets/Dialogues/iceBossDialogue.json", dialogueSpawn, pseudoTexture));

	activeFrame = { 0,0,-(float)32 * enemy.GetDirection(), 32 };
}

std::shared_ptr<EState> IBBeforeFight::Update(Enemy& enemy)
{
	stateFrameCounter++;
	if (stateFrameCounter >= 15) {
		thisFrame++;
		stateFrameCounter = 0;
	}
	if (thisFrame >= 3)  thisFrame = 0;
	activeFrame = { (float)32 * thisFrame,0,-(float)32 * enemy.GetDirection(), 32 };

	if (IsKeyPressed(KEY_E) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_UP)) textCounter++;
	if (textCounter >= 11) {
		for (const auto& dialogue : sceneManager->GetInteractables()) {
			if (dialogue->GetInteractableType() == InteractableType::TmpDialogObj) dialogue->MarkToDestroy();
		}
		sceneManager->GetActiveScene()->ToggleMusic();
		return std::make_shared<IBSeek>(enemy);
	}

	return shared_from_this();
}

void IBBeforeFight::Draw(Enemy& enemy)
{
	auto* iceBoss = dynamic_cast<IceBoss*>(&enemy);
	iceBoss->DrawDirectional(iceBoss->GetPosition(), iceBoss->GetTexture(), activeFrame);
}
