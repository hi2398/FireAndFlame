#pragma once

#include "../Core/Object.h"
enum class HeartState {Good, Bad};

class HeartObject : public Object {
public:
	HeartObject(Vector2 initialPos, HeartState heartState, int lifetime);
	void Update() override;
	void UpdatePos(Vector2 updatedPos);
	void Draw() override;
protected:

private:
	int frameCounter = 0;
	int lifetime = 0;
	int yOffset = 0;
	Texture2D texture{};
	HeartState heartState;
};