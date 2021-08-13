#pragma once

#include "../../Core/EState.h"
#include "MinerBoss.h"

enum class TransitionStep{MoveToStart, Jump, MoveToEnd};

class MBPhaseTransitionState : public EState {
public:
    explicit MBPhaseTransitionState(Enemy &enemy);
    std::shared_ptr <EState> Update(Enemy &actor) override;
    void Draw(Enemy &actor) override;
    ~MBPhaseTransitionState() override = default;

protected:


private:
    TransitionStep currentStep{TransitionStep::MoveToStart};
    bool done{false};
    const Vector2 jumpStart{64 * 32, 90 * 32};
    Direction nextJump{Direction::LEFT};
    Vector2 nextJumpLoc{62 * 32, 88 * 32};
    Vector2 jumpStartLoc{};
    float lerpAlpha{0.f};
    int jumpsLeft{19};
    Vector2 targetFloorLocStart {};
    Vector2 targetFloorLoc{61*32,53*32};
    bool correctZ{false};
    int endJumpStep{0};

    void MoveToStart(Enemy& enemy);
    void Jump(Enemy& enemy);
    void MoveToEnd(Enemy& enemy);
};


