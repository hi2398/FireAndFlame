#pragma once
#include "raylib.h"
#include "../Global.h"
#include "../Core/Interactable.h"
#include <iostream>



class Coal : public Interactable
{
public:
	Coal(Vector2 location={0, 0});
	void Interact(Actor& actor)override;
	Rectangle GetHitbox();
	void Update() override;
	void Draw() override;
	~Coal() override;

private:
	static constexpr int fuel = 25;
	Texture2D texture;
	Rectangle hitbox{};
	bool isGrounded = false;
	float fallSpeed = 1.5f;
	float gravityMultiplier = 1.5f;


};

