#pragma once


class PlayerController {
public:
    void HandleInput();
    ~PlayerController() = default;
 
protected:

private:
    const int right = 1;
    const int left = -1;

};


