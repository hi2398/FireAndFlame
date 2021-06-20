#pragma once

#include "../../Core/Observer/Observer.h"

class PlayerObserver : public Observer {
public:
    explicit PlayerObserver(Actor &actor);
    ~PlayerObserver() override;

    void OnNotify(Event event) override;

protected:

private:
};


