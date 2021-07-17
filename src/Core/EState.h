#pragma once

#include <memory>
#include "Enemy.h"


class EState : public std::enable_shared_from_this<EState> {
public:

    [[nodiscard]] virtual std::shared_ptr<EState> Update(Enemy& enemy) = 0;
    virtual void Draw(Enemy& enemy) = 0;
    virtual ~EState() = default;
protected:

private:

};