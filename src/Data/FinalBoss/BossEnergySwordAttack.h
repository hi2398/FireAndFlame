#include "../../Core/Interactable.h"

class BossEnergySwordAttack : public Interactable{
public:
    BossEnergySwordAttack(Vector2 position,bool attackDirection, int prepareCounter);
    void Interact(Actor &actor) override;
    void Update() override;
    void Draw() override;
    ~BossEnergySwordAttack() override;
private:
    Texture2D texture;
    Rectangle drawBox = {0,0,32,128};

    bool direction = false; //false = von rechts nach links, true = von links nach rechts
    Vector2 attackPoint;
    Vector2 moveTowardsPosition;

    bool hasDamagedPlayer = false;

    int magnitude = 25; // speed of energy attack
    int prepareCounter = 120; // how long the energy attack needs until it flies towards the player
    int counter = 20;
protected:
};