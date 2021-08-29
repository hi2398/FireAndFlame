#pragma once

#include "../../Core/Interactable.h"
#include "../../Global.h"

class Fireball : public Interactable {
public:
	Fireball(Vector2 initialPosition, Vector2 direction, ObjectTypes user);
	void Update() override;
	void Interact(Actor& actor) {};
	void Draw() override;
	~Fireball() {};
protected:

private:
	ObjectTypes user;
	Texture2D fireball{};
	int fireballCounter = 0;
	int fireballFrame = 0;
	Vector2 direction = {0,0};
	Rectangle fireballRec{};

	Rectangle tileRec{0,0,32,32};

	Sound fireballSFX;
};