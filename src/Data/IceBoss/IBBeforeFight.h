#pragma once

#include <iostream>
#include "../../Core/EState.h"

class IBBeforeFight : public EState {
public:
    IBBeforeFight(Enemy& enemy);
    std::shared_ptr <EState> Update(Enemy& enemy) override;
    void Draw(Enemy& enemy) override;
    ~IBBeforeFight() override = default;

protected:


private:
    Texture2D pseudoTexture;
    Rectangle texRec;
    int textCounter = 0;
};
