#include "TBBeforeFightState.h"
#include "TBIdleState.h"
#include "../../Global.h"
#include "../../Data/TmpDialogueObject.h"

TBBeforeFightState::TBBeforeFightState(Enemy& enemy) : EState(enemy)
{
	pseudoTexture.width = 20 * 32;
	pseudoTexture.height = 20 * 32;
	dialoguePath = ""; // TODO Ask amar how this works
	Vector2 dialogueSpawn = { 49 * 32, 75 * 32 };

	/*sceneManager->AddInteractable(std::make_unique<TmpDialogueObject>(dialoguePath, dialogueSpawn, pseudoTexture));*/
	sceneManager->AddInteractable(std::make_unique<TmpDialogueObject>("assets/Dialogues/tutorialText1.json", dialogueSpawn, pseudoTexture));

}

std::shared_ptr<EState> TBBeforeFightState::Update(Enemy& enemy)
{
	if (IsKeyPressed(KEY_E) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_UP)) textCounter++;
	std::cout << textCounter << "\n";
	if (textCounter >= 8) {
		sceneManager->GetInteractables().back()->MarkToDestroy();
		return std::make_shared<TBIdleState>(enemy);
	}
	return shared_from_this();
}

void TBBeforeFightState::Draw(Enemy& enemy)
{
	DrawTexture(enemy.GetTexture(), enemy.GetPosition().x, enemy.GetPosition().y, WHITE);
}
