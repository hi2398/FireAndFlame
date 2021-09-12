#include "Fireball.h"

Fireball::Fireball(Vector2 initialPosition, Vector2 direction, ObjectTypes user) : Interactable(InteractableType::Fireball)
{
	position = initialPosition;
    this->direction = direction;
    this->user = user;
	fireball = LoadTexture("assets/graphics/projectiles/Firebolt_Sheet.png");
    soundManager->PlaySfx(SFX::FIREBALL);
}

void Fireball::Update()
{
    //projectile frames
    fireballCounter++;
    if (fireballCounter >= 5) {
        fireballCounter = 0;
        fireballFrame++;
    }
    fireballRec = { (float)32 * fireballFrame , 0, (float)32 * direction.x , 32 };
    interactionZone = {position.x, position.y, 32, 16};

    position.x += 8.0f * direction.x;
    position.y += 8.0f * direction.y;

    if (user == ObjectTypes::Player) {
        for (const auto& enemies : sceneManager->GetEnemies()) {
            if (CheckCollisionRecs(enemies->GetCollider(), interactionZone) && !enemies->IsInvulnerable()) {
                enemies->ReceiveDamage(3);
                enemies->SetInvulnerable(true);
                Vector2 tmp = { enemies->GetPosition().x + 8, enemies->GetPosition().y + 5 };
                sceneManager->AddInteractable(std::make_unique<HitMarker>(tmp));
                MarkToDestroy();
            }
        }
    }
    else if (user == ObjectTypes::Enemy) {
        if (CheckCollisionRecs(playerCharacter->playerHitbox, interactionZone)) {
            if (!playerCharacter->IsInvulnerable()) playerCharacter->SetInvulnerable(true), playerCharacter->SetHealth(playerCharacter->GetHealth() - 10);
            MarkToDestroy();
        }
    }


    for (const auto& tile : sceneManager->GetTilemap()->GetTileColliders()) {
        tileRec.x = tile.x;
        tileRec.y = tile.y;
        if (CheckCollisionRecs(tileRec, interactionZone)) {
            markedDestroy = true;
        }
    }

}

void Fireball::Draw()
{
    DrawTextureRec(fireball, fireballRec, position, WHITE);
}

Fireball::~Fireball() {
    UnloadTexture(fireball);
}