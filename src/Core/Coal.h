#pragma once
#include "Interactable.h"
#include "raylib.h"
#include "../Global.h"

class Coal:public Interactable
{
public:
	Coal();
	void Interact()override;
	void SetPosition(Vector2 Pos);
	void SetTexture(Texture2D Texture);
	void Update();
	void Draw();
	~Coal();

private:
	int Fuel = 10;
	Texture2D aTexture;
	Rectangle aHitbox;
	Vector2 aPos;
	bool isGounded;
};

