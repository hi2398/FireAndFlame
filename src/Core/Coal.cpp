#include "Coal.h"

Coal::Coal()
{
	aTexture = LoadTexture("assets/graphics/Coal.png");
}

void Coal::Interact()
{
	if (aEnabled == true)
	{
		playerCharacter->SetHealth(playerCharacter->GetHealth() + aFuel);
		aEnabled = false;
		aFallSpeed = 1.5*aGravityMultiplyer;
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

bool Coal::GetGrounded()
{
	return aisGounded;
}

bool Coal::GetEnabled()
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
	{	//Wenn es nicht Am Boden ist, fällt es runter
		aPos.y += aFallSpeed;
		aFallSpeed += 0.1f;
	}
	aHitbox.width = aTexture.width;
	aHitbox.height = aTexture.height;
	aHitbox.x = aPos.x;
	aHitbox.y = aPos.y;

}

void Coal::Draw()
{
	if (aEnabled == true)
	{
		DrawTexture(aTexture, aPos.x, aPos.y, WHITE);
	}
}

Coal::~Coal()
{
	UnloadTexture(aTexture);
}
