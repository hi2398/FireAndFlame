#pragma once

#include "../../Core/EState.h"

class MBSummonState : public EState {
public:
    explicit MBSummonState(Enemy &enemy);
    std::shared_ptr<EState> Update(Enemy &actor) override;
    void Draw(Enemy &actor) override;
    ~MBSummonState() override = default;

protected:


private:


};


