#pragma once

#include "../../Core/EState.h"

class MBRangedState : public EState {
public:
    explicit MBRangedState(Enemy &enemy);
    std::shared_ptr<EState> Update(Enemy &actor) override;
    void Draw(Enemy &actor) override;
    ~MBRangedState() override = default;

protected:


private:


};


