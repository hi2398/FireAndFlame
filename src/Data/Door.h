#pragma once

#include "../Core/Interactable.h"
#include <raylib.h>

class Door : public Object {
public:
	Door(Vector2 position, bool isOpen = true);
	void Update() override;
	void Draw() override;
	void SetIsOpen(bool isOpen);
	~Door();
private:
	bool isOpen;
	Texture2D texture;
	Rectangle activeFrame = { 8 * 32, 4 * 32, 32, 2 * 32 };
};