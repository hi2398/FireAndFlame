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

void Coal::SetGrounded(bool pIsGroudned)
{
	aisGounded = pIsGroudned;
}

bool Coal::GetGrounded() const
{
	return aisGounded;
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
	if (!aisGounded)
	{	//Wenn es nicht Am Boden ist, f�llt es runter
		aPos.y += aFallSpeed;
		aFallSpeed += 0.1f;
	}
	aHitbox.width = aTexture.width - 6;
	aHitbox.height = aTexture.height;
	aHitbox.x = aPos.x + 3;
	aHitbox.y = aPos.y;

}

void Coal::Draw()
{
	if (aEnabled)
	{
		DrawTexture(aTexture, aPos.x, aPos.y, WHITE);
	}
}

Coal::~Coal()
{
	UnloadTexture(aTexture);
}
