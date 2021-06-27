#pragma once

#include "../../Core/Observer/Observer.h"

class PlayerObserver : public Observer {
public:
    explicit PlayerObserver(Actor &actor);
    ~PlayerObserver() override;

    void OnNotify(EVENT event) override;

protected:

private:
};


