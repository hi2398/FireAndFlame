#include "Coal.h"

Coal::Coal()
{
}

void Coal::Interact()
{
	playerCharacter->SetHealth(playerCharacter->GetHealth() + Fuel);
}

void Coal::SetPosition(Vector2 Pos)
{
	aPos = Pos;
}

void Coal::SetTexture(Texture2D Texture)
{
	aTexture = Texture;
}

void Coal::Update()
{
	if (!isGounded) 
	{	//Wenn es nicht Am Boden ist, fällt es runter
		aPos.y += 0.1f;
	}
}

void Coal::Draw()
{
	DrawTexture(aTexture, aPos.x, aPos.y, WHITE);
}

Coal::~Coal()
{
}
