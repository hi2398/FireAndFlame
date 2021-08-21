#pragma once

#include "../../Core/EState.h"


class IceBoss;

enum class NextSeekAction{Melee, Ranged, Decide};

class IBSeek : public EState {
public:
    IBSeek(Enemy &enemy);
    std::shared_ptr <EState> Update(Enemy &enemy) override;
    void Draw(Enemy &enemy) override;
    ~IBSeek() override = default;

protected:


private:
    static void CalcWalkingDirection(Actor& actor, Vector2 targetLoc);
    NextSeekAction nextAction{NextSeekAction::Decide};
    std::shared_ptr<EState> MeleeApproach(Enemy& enemy);
    std::shared_ptr<EState> RangedMove(Enemy &enemy);
    const Vector2* rangedSpot{nullptr};
    static constexpr Vector2 leftRangedSpot{24*32, 33*32};
    static constexpr Vector2 rightRangedSpot{33*32, 33*32};
    const Vector2 jumpStart{29*32, 36*32};
    bool jumpStarted{false};
    int rangedTimer{60};
    Rectangle texRec;
};


