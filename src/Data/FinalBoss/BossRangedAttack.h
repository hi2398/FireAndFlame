#include "../../Core/Interactable.h"

class BossRangedAttack : public Interactable{
public:
    BossRangedAttack(Vector2 pos);
    void Interact(Actor &actor) override;
    void Update() override;
    void Draw() override;
    ~BossRangedAttack() override = default;

private:
    Texture2D texture;
    int existCounter = 120;
    Vector2 attackPoint;
    Vector2 moveTowardsPosition;
    int magnitude = 50;
protected:
};
