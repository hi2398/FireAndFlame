#pragma once
#include "../../Core/Interactable.h"

class Toast : public Interactable {
public:
	Toast(Vector2 initialPosition);
	void Update() override;
	void Draw() override;
	void Interact(Actor& actor) override;
	~Toast();
protected:

private:
	Texture2D toastTexture;
	bool ToastIsBurned{ false };

	float toastSpeed = 5.0f;
	float toastDistance= 3.0f;
	float toastGravity = 0.2f;
	float attackDirection = 1;
	int existenceCounter = 0;
	float revert = 1.0f;

	float yDiff;
	float xDiff;

};