#pragma once

#include "../Core/Interactable.h"


class HitMarker : public Interactable {
public:
	HitMarker(Vector2 initialPos);
	void Update() override;
	void Interact(Actor& actor) override {};
	void Draw() override;
	~HitMarker();
protected:

private:
	int frameCounter = 0;
	Texture2D texture{};
	Rectangle activeFrame{};
	int thisFrame = 0;
};