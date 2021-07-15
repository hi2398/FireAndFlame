#pragma once
#include "../../Core/Enemy.h"

class ToastCat : public Enemy
{
public:
	explicit ToastCat(Vector2 initalLoc);
	void Update() override;
	void Draw() override;
	~ToastCat() override;

private:
	void StartAttack();
	Vector2 toastPos;
	Rectangle toastHitbox;
	Texture2D toastTexture;
	const int shootingRange = 160;
	const int discomfortRange = 10;
	const int movementSpeed = 2;
	bool toastActive=false;
	Vector2 edgeSeekerRight;
	Vector2 edgeSeekerLeft;
	Vector2 flightCenter;
	float tossXModifier;
	float tossYModifier;
	bool onScreen;
};

