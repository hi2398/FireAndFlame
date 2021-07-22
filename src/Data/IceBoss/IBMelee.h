#pragma once


#include "../../Core/State.h"

class IBMelee : public State {
public:
    IBMelee();
    std::shared_ptr <State> Update(Actor &actor) override;
    void Draw(Actor &actor) override;
    ~IBMelee() override = default;

protected:


private:
    int meleeTimer{60};
    float attackCollisionRad{16};
    const int meleeDamage{5};
    bool playerHit{false}; //prevent multihits

};


