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
	bool GetGrounded() const;
	bool GetEnabled() const;
	void SetEnabled(bool pEnabled);
	Rectangle GetHitbox();
	void Update() override;
	void Draw() override;
	~Coal() override;

private:
	int aFuel = 10;
	Texture2D aTexture{};
	Vector2 aPos{};
	Rectangle aHitbox{};
	bool aisGounded = false;
	bool aEnabled = false;
	float aFallSpeed = 1.5f;
	float aGravityMultiplyer = 1.5f;
};

