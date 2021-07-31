#include "../../Core/Object.h"

class ChasingBoss : public Object{
public:
    ChasingBoss(Vector2 position);
    void Update() override;
    void Draw() override;
    void MovePosition(Vector2 newPosition);

private:
    int magnitude = 25;
    Vector2 currentPosition;
    Vector2 targetPosition;
    Texture2D texture;
protected:
};
