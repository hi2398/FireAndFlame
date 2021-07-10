#include "SaveGameState.h"
#include "../Global.h"
#include "../json.hpp"
#include <iomanip>

using namespace nlohmann;

SaveGameState::SaveGameState() {}

SaveGameState::~SaveGameState() {

}

void SaveGameState::SaveGame(const std::string& saveFileLoc) {
    int playerHealth =playerCharacter->GetHealth();
    Vector2 playerLocation = playerCharacter->GetPosition();


    json saveDataStruct = {
            {"player", //START PLAYER
             {
                {"health", playerHealth},
                {"locationX", playerLocation.x},
                {"locationY", playerLocation.y}
             }
            } //END PLAYER
    };

    std::ofstream saveFile{saveFileLoc};
    saveFile << std::setw(4) << saveDataStruct;
    saveFile.close();

}

void SaveGameState::LoadGame(const std::string& saveFileLoc) {

}
