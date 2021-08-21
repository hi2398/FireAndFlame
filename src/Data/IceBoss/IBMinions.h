#pragma once

#include "../../Core/EState.h"

class IBMinions : public EState {
public:
    IBMinions(Enemy &enemy);
    std::shared_ptr <EState> Update(Enemy &enemy) override;
    void Draw(Enemy &enemy) override;
    ~IBMinions() override = default;

protected:


private:


};
