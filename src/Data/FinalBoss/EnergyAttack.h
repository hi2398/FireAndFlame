#include "../../Core/Interactable.h"
class EnergyAttack : public  Interactable{
public:
    EnergyAttack(Vector2 position);
    void Interact(Actor &actor) override;
    void Update() override;
    void Draw() override;
    ~EnergyAttack() override;
private:
    Texture2D texture;

    Vector2 energyAttackPosition;
    Vector2 attackPoint;
    Vector2 moveTowardsPosition;

    bool allowedToDamagePlayer = false;

    Rectangle drawZone = {0,0,32,32};
    int counter = 20;

    int magnitude; // speed of energy attack
    int prepareCounter = 120; // how long the energy attack needs until it flies towards the player
protected:
};
