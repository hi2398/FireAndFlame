#pragma once
#include "Interactable.h"
#include "../Global.h"

class Coal:public Interactable
{
public:
	Coal();
	void Interact()override;
	~Coal();

private:
	int Feul = 10;
};

