#pragma once
#include <memory>
#include "ObjectTypes.h"
#include "raylib.h"

class Object : public std::enable_shared_from_this<Object> {
public:
    explicit Object(ObjectTypes type);
    virtual void Update() = 0;
    virtual void Draw() = 0;

    //Getter and Setter
    void SetPosition(Vector2 position);
    [[nodiscard]] Vector2 GetPosition() const;
    [[nodiscard]] ObjectTypes GetType() const;
    [[nodiscard]] bool IsMarkedDestroy() const;
    [[nodiscard]] void MarkToDestroy();

    virtual ~Object() = default;

protected:
    ObjectTypes type;
    Vector2 position{};

    bool markedDestroy{false};
};


