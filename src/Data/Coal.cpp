#include "Coal.h"
#include "../Global.h"


Coal::Coal(Vector2 location) : Interactable(InteractableType::Coal)
{
    position=location;
    texture = LoadTexture("assets/graphics/Coal.png");
    hitbox.width = static_cast<float>(texture.width - 6);
    hitbox.height = static_cast<float>(texture.height);
    hitbox.x = position.x + 3;
    hitbox.y = position.y;
    interactionZone.x=hitbox.x;
    interactionZone.y=hitbox.y;
}

void Coal::Interact(Actor& actor)
{
    if (playerCharacter->GetHealth() <= 75) playerCharacter->SetHealth(playerCharacter->GetHealth() + fuel);
    else {
        playerCharacter->SetHealth(100);
    }
    markedDestroy=true;
}








Rectangle Coal::GetHitbox()
{
	return hitbox;
}

void Coal::Update()
{

    if (!isGrounded) {
        for (const auto &collTile : sceneManager->GetTilemap()->GetTileColliders()) {

            Rectangle collidingRectangle{collTile.x, collTile.y, 32, 32};

            if (CheckCollisionRecs(collidingRectangle, hitbox)) {
                isGrounded = true;
                SetPosition({position.x, collTile.y - 32.0f});
                return;
            }
        }
    }

    if (!isGrounded)
	{
		position.y += fallSpeed;
        fallSpeed += 0.1f;
        hitbox.x = position.x + 3;
        hitbox.y = position.y;
        interactionZone.y=hitbox.x;
        interactionZone.y=hitbox.y;
	}

}

void Coal::Draw()
{
		DrawTexture(texture, static_cast<int>(position.x), static_cast<int>(position.y), WHITE);
}

Coal::~Coal()
{

}
