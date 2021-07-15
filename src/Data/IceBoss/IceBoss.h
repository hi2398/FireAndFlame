#pragma once

#include "../../Core/Enemy.h"

class IceBoss : public Enemy {
public:

    IceBoss();
    void Update() override;
    void Draw() override;
    ~IceBoss() override = default;

protected:


private:


};


