#pragma once

//created by Robin on 29.06.2021
#include "../Core/Enemy.h"

class ToastCat : public Enemy
{
public:
	ToastCat(float pStartX, float pStartY);
	void Update() override;
	void Draw() override;
	~ToastCat();

private:
	void StartAttack();
	Vector2 aToastPos;
	Rectangle aToastHitbox;
	Texture2D aToastTexture;
	const int aShootingRange = 160;
	const int aDiscomfortRange = 10;
	const int aMovementSpeed = 2;
	bool aToastActive=false;
	Vector2 aEdgeSeekerRight;
	Vector2 aEdgeSeekerLeft;
	Vector2 aFlightcenter;
	float aTossXModifier;
	float aTossYModifier;
};

