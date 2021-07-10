#pragma once
#include <string>

class SaveGameState {
public:
    SaveGameState();
    ~SaveGameState();

    void SaveGame(const std::string& saveFileLoc);
    void LoadGame(const std::string& saveFileLoc);

protected:


private:


};


