#pragma once

#include <memory>
#include "Enemy.h"


class EState : public std::enable_shared_from_this<EState> {
public:
    EState(Enemy& enemy);
    [[nodiscard]] virtual std::shared_ptr<EState> Update(Enemy& enemy) = 0;
    virtual void Draw(Enemy& enemy) = 0;
    virtual ~EState() = default;
protected:
    Rectangle activeFrame{};
    Rectangle activeFrame2{};
    int stateFrameCounter = 0;
    int thisFrame = 0;
    int thisFrame2 = 0;
    Vector2 trianglePoint1{};
    Vector2 trianglePoint2{};
private:

};