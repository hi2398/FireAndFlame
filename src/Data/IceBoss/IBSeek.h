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
    static void CalcWalkingDirection(Actor& actor, Vector2 targetLoc);
    NextSeekAction nextAction{NextSeekAction::Decide};
    std::shared_ptr<State> MeleeApproach(Actor& actor);
    std::shared_ptr<State> RangedMove(Actor& actor);
    const Vector2* rangedSpot{nullptr};
    static constexpr Vector2 leftRangedSpot{26*32, 33*32};
    static constexpr Vector2 rightRangedSpot{33*32, 33*32};
    const Vector2 jumpStart{29*32, 36*32};
    bool jumpStarted{false};
    int rangedTimer{60};
};


