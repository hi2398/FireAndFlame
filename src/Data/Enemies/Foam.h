#pragma once

#include "../../Global.h"
#include "../../Core/Interactable.h"

class Foam : public Interactable {
public:
	Foam(Vector2 initialPosition);
	void Update() override;
	void Draw() override;
	void Interact(Actor& actor) override;
	~Foam() {};
protected:

private:
	Texture2D foamTexture;
	Vector2 playerReference;
	Vector2 shootToPlayer;

	float speed = 5.0f;
};