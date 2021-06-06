#pragma once
#include "Interactable.h"
#include "raylib.h"
#include "../Global.h"
#include <iostream>

/*This Class was made by Robin. Therefore following prefixes apply:
For an Attribute the prefix "a" applies
For a Parameter the prefix "p" applies
*/



class Coal:public Interactable
{
public:
	Coal();
	void Interact()override;
	void SetPosition(Vector2 pPos);
	void SetTexture(Texture2D pTexture);
	void SetGrounded(bool pIsGroudned);
	bool GetGrounded();
	bool GetEnabled();
	void SetEnabled(bool pEnabled);
	Rectangle GetHitbox();
	void Update();
	void Draw();
	~Coal();

private:
	int aFuel = 10;
	Texture2D aTexture{};
	Vector2 aPos{};
	Rectangle aHitbox{};
	bool aisGounded = false;
	bool aEnabled = false;
	int aFallSpeed = 1.5;
	int aGravityMultiplyer = 1.5;
};

