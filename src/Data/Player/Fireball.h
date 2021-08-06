#pragma once

#include "../../Core/Interactable.h"
#include "../../Global.h"

class Fireball : public Interactable {
public:
	Fireball(Vector2 initialPosition, int direction, ObjectTypes user);
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
	int direction = 0;
	Rectangle fireballRec{};
};