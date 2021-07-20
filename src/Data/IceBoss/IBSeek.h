#pragma once

#include "../../Core/State.h"

enum class NextSeekAction{Melee, Ranged, Decide};

class IBSeek : public State {
public:
    IBSeek();
    std::shared_ptr <State> Update(Actor &actor) override;
    void Draw(Actor &actor) override;
    ~IBSeek() override = default;

protected:


private:
    NextSeekAction nextAction{NextSeekAction::Decide};
    std::shared_ptr<State> MeleeApproach(Actor& actor);
    std::shared_ptr<State> RangedMove(Actor& actor);
    const Vector2* rangedSpot{nullptr};
    static constexpr Vector2 leftRangedSpot{23*32, 36*32};
    static constexpr Vector2 rightRangedSpot{34*32, 36*32};
};


