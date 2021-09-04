#pragma once
#include "raylib.h"
#include "../../Core/Object.h"

class FreezeVisual : public Object {
public:
	FreezeVisual(Vector2 spawn, int lifetime);
	~FreezeVisual() override = default;
	void Update() override;
	void Draw() override;
private:
	Vector2 position{};
	Texture2D texture;
	int lifetime{};
};