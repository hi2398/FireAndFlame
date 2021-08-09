#include "Fireball.h"

Fireball::Fireball(Vector2 initialPosition, int direction, ObjectTypes user) : Interactable(InteractableType::Fireball)
{
	position = initialPosition;
    this->direction = direction;
    this->user = user;
	fireball = LoadTexture("assets/graphics/projectiles/Firebolt_Sheet.png");
}

void Fireball::Update()
{
    //projectile frames
    fireballCounter++;
    if (fireballCounter >= 5) {
        fireballCounter = 0;
        fireballFrame++;
    }
    fireballRec = { (float)32 * fireballFrame , 0, (float)32 * direction , 32 };
    interactionZone = {position.x, position.y, 32, 16};

    position.x += 8.0f * direction;

    if (user == ObjectTypes::Player) {
        for (const auto& enemies : sceneManager->GetEnemies()) {
            if (CheckCollisionRecs(enemies->GetCollider(), interactionZone) && !enemies->IsInvulnerable()) {
                enemies->ReceiveDamage(10);
                enemies->SetInvulnerable(true);
            }
        }
    }
    else if (user == ObjectTypes::Enemy) {
        if (CheckCollisionRecs(playerCharacter->playerHitbox, interactionZone)) {
            if (!playerCharacter->IsInvulnerable()) playerCharacter->SetInvulnerable(true), playerCharacter->SetHealth(playerCharacter->GetHealth() - 10);
        }
    }
}

void Fireball::Draw()
{
    DrawTextureRec(fireball, fireballRec, position, WHITE);
}


