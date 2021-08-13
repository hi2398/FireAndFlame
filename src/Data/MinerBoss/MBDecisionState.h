#pragma once

#include <ostream>
#include "../../Core/EState.h"

class MBDecisionState : public EState {
public:
    explicit MBDecisionState(Enemy &enemy);
    std::shared_ptr <EState> Update(Enemy &actor) override;
    void Draw(Enemy &actor) override;
    ~MBDecisionState() override = default;

protected:


private:
    static std::shared_ptr<EState> DecideByChance(Enemy& actor);
    int delay{30};

};


