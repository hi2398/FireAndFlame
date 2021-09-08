#include "SceneChangerObject.h"
#include "../Global.h"
#include "../Scenes/NeutralArea.h"
#include "../Scenes/AreaOne.h"
#include "../Scenes/AreaTwo.h"
#include "../Scenes/AreaThree.h"
#include "../Scenes/IceBossScene.h"
#include "../Scenes/FinalBoss.h"
#include "../Scenes/MinerBossScene.h"
#include "../Scenes/TraitorBossScene.h"

SceneChangerObject::SceneChangerObject(Vector2 location, SceneEnums nextScene, SceneEnums thisScene) : Interactable(InteractableType::SceneChangeCollider) {
	comingFromThisScene = thisScene;
	position = location;
	chosenScene = nextScene;
	interactionZone = { position.x,position.y,128,128 };
}

void SceneChangerObject::Interact(Actor& actor) {
	playerCharacter->BlockPlayerControls(true);
	sceneIsChanging = true;
	playerCharacter->HoldInPlace(true, {playerCharacter->GetPosition()});
	
}

void SceneChangerObject::Update() {
	if (sceneIsChanging) {
		fadeOutCounter += 3;
		if (fadeOutCounter >= 255) fadeOutCounter = 255, fadeOutcomplete = true;
		sceneManager->GetActiveScene()->FadeOutOfScene(fadeOutCounter);
	}

	if (fadeOutcomplete) {
		playerCharacter->BlockPlayerControls(false);
		playerCharacter->HoldInPlace(false, { 0 });
		switch (chosenScene) {
		case SceneEnums::NeutralArea:
			sceneManager->SetNextScene(std::make_unique<NeutralArea>(comingFromThisScene));
			break;
		case SceneEnums::AreaOne:
			sceneManager->SetNextScene(std::make_unique<AreaOne>(comingFromThisScene));
			break;
		case SceneEnums::IceBoss:
			sceneManager->SetNextScene(std::make_unique<IceBossScene>(comingFromThisScene));
			break;
		case SceneEnums::AreaTwo:
			sceneManager->SetNextScene(std::make_unique<AreaTwo>(comingFromThisScene));
			break;
		case SceneEnums::FinalBoss:
			sceneManager->SetNextScene(std::make_unique<FinalBoss>(comingFromThisScene));
			break;
		case SceneEnums::MinerBoss:
			sceneManager->SetNextScene(std::make_unique<MinerBossScene>(comingFromThisScene));
			break;
		case SceneEnums::TraitorBoss:
			sceneManager->SetNextScene(std::make_unique<TraitorBossScene>(comingFromThisScene));
			break;
		case SceneEnums::AreaThree:
			sceneManager->SetNextScene(std::make_unique<AreaThree>(comingFromThisScene));
			break;
		}
	}
}

void SceneChangerObject::Draw() {
	DrawRectangleRec(interactionZone, GREEN);
}
