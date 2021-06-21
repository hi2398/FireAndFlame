#pragma once
#include <memory>
#include "ObjectTypes.h"
#include "raylib.h"

class Object : public std::enable_shared_from_this<Object> {
public:
    explicit Object(ObjectTypes type);
    virtual void Update() = 0;
    virtual void Draw() = 0;
    Vector2 GetPosition() const;
    void SetPosition(Vector2 position);
    [[nodiscard]] ObjectTypes GetType() const;
    virtual ~Object() = default;

protected:
    ObjectTypes type;
    Vector2 position{};
private:

};


