#include "Coal.h"

Coal::Coal()
{
}

void Coal::Interact()
{
	playerCharacter->SetHealth(playerCharacter->GetHealth() + Feul);
}

Coal::~Coal()
{
}
