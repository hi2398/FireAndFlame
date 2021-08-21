#pragma once


#include "../../Core/EState.h"

class IBMelee : public EState {
public:
    IBMelee(Enemy &enemy);
    std::shared_ptr <EState> Update(Enemy &enemy) override;
    void Draw(Enemy &enemy) override;
    ~IBMelee() override = default;

protected:


private:
    int meleeTimer{60};
    float attackCollisionRad{16};
    const int meleeDamage{5};
    bool playerHit{false}; //prevent multihits
    Rectangle texRec;

};


