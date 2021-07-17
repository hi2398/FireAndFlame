#pragma once

#include "../../Core/EState.h"

class StunnedState : public EState {
public:
    std::shared_ptr <EState> Update(Enemy& enemy) override;
    void Draw(Enemy& enemy)override;

    ~StunnedState() = default;

protected:


private:
    int stunnedFrameCounter = 0;
    int stunnedOffset = 0;
};