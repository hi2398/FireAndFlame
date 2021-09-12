#pragma once

#include <iostream>
#include "../../Core/EState.h"

class MBBeforeFight : public EState {
public:
    MBBeforeFight(Enemy& enemy);
    std::shared_ptr <EState> Update(Enemy& actor) override;
    void Draw(Enemy& actor) override;
    ~MBBeforeFight() override = default;

protected:


private:
    Texture2D pseudoTexture;
    Rectangle texRec;
    int textCounter = 0;

};