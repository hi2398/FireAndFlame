#pragma once
#include <memory>
#include "Core/Scene.h"
#include "Core/GameMode.h"
#include "Scenes/MainMenu.h"
#include "GameData/IgnitePlayerController.h"
#include "GameData/IgnitePlayerCharacter.h"
#include "GameData/IgniteHUD.h"

std::unique_ptr<Scene> initialScene=std::make_unique<MainMenu>();
std::unique_ptr<GameMode> initialGameMode=std::make_unique<GameMode>(std::make_shared<IgnitePlayerCharacter>(),
        std::make_shared<IgnitePlayerController>(), std::make_shared<IgniteHUD>());
