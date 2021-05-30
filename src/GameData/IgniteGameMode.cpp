#include "IgniteGameMode.h"


IgniteGameMode::IgniteGameMode() : GameMode(std::make_unique<IgnitePlayerCharacter>(), std::make_unique<IgnitePlayerController>(), std::make_unique<IgniteHUD>()) {

}
