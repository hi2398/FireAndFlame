#include "../../Global.h"
#include "MinerBoss.h"
#include "MBBeforeFight.h"
#include "../../Data/TmpDialogueObject.h"
#include "MBDecisionState.h"

MBBeforeFight::MBBeforeFight(Enemy& enemy) : EState(enemy)
{
	activeFrame = { (float)32 * thisFrame,0,-(float)32 * enemy.GetDirection(), 32 };
	pseudoTexture.width = 20 * 32;
	pseudoTexture.height = 20 * 32;
	Vector2 dialogueSpawn = { 42 * 32, 82 * 32 };
	sceneManager->AddInteractable(std::make_unique<TmpDialogueObject>("assets/Dialogues/minerBossDialogue.json", dialogueSpawn, pseudoTexture));
}

std::shared_ptr<EState> MBBeforeFight::Update(Enemy& actor)
{
	auto* minerBoss = dynamic_cast<MinerBoss*>(&actor);
	stateFrameCounter++;
	if (stateFrameCounter >= 15) {
		thisFrame++;
		stateFrameCounter = 0;
	}
	if (thisFrame >= 3)  thisFrame = 0;
	activeFrame = { (float)32 * thisFrame,0,-(float)32 * minerBoss->GetDirection(), 32 };

	if (IsKeyPressed(KEY_E) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_UP)) textCounter++;
	if (textCounter >= 10) {
		for (const auto& dialogue : sceneManager->GetInteractables()) {
			if (dialogue->GetInteractableType() == InteractableType::TmpDialogObj) dialogue->MarkToDestroy();
		}
		sceneManager->GetActiveScene()->ToggleMusic();
		return std::make_shared<MBDecisionState>(actor);
	}

	return shared_from_this();
}

void MBBeforeFight::Draw(Enemy& actor)
{
	auto minerBoss = dynamic_cast<MinerBoss&>(actor);
	minerBoss.DrawDirectional(minerBoss.GetPosition(), minerBoss.GetTexture(), activeFrame);
}
