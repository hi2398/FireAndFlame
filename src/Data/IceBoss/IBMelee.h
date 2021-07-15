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


};


