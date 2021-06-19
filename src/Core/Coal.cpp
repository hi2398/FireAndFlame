#include "Coal.h"

Coal::Coal()
{
	aTexture = LoadTexture("assets/graphics/Coal.png");
}

void Coal::Interact()
{
	if (aEnabled)
	{
		if (playerCharacter->GetHealth() <= 90) playerCharacter->SetHealth(playerCharacter->GetHealth() + aFuel);
		else {
			playerCharacter->SetHealth(100);
		}
		aEnabled = false;
		aFallSpeed = 1.5f*aGravityMultiplyer;
	}
}

void Coal::SetPosition(Vector2 pPos)
{
	aPos = pPos;
}

void Coal::SetTexture(Texture2D pTexture)
{
	aTexture = pTexture;
}

void Coal::SetGrounded(bool pIsGrounded)
{
    aisGrounded = pIsGrounded;
}

bool Coal::GetGrounded() const
{
	return aisGrounded;
}

bool Coal::GetEnabled() const
{
	return aEnabled;
}

void Coal::SetEnabled(bool pEnabled)
{
	aEnabled = pEnabled;
}




Rectangle Coal::GetHitbox()
{
	return aHitbox;
}

void Coal::Update()
{
	if (!aisGrounded)
	{	//Wenn es nicht Am Boden ist, faellt es runter
		aPos.y += aFallSpeed;
		aFallSpeed += 0.1f;
	}
	aHitbox.width = static_cast<float>(aTexture.width - 6);
	aHitbox.height = static_cast<float>(aTexture.height);
	aHitbox.x = aPos.x + 3;
	aHitbox.y = aPos.y;

}

void Coal::Draw()
{
	if (aEnabled)
	{
		DrawTexture(aTexture, static_cast<int>(aPos.x), static_cast<int>(aPos.y), WHITE);
	}
}

Coal::~Coal()
{
	UnloadTexture(aTexture);
}
