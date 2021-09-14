#pragma once

#include "../Global.h"
#include "Coal.h"
#include "../Core/Interactable.h"
#include "../Core/EnemyList.h"

enum class SpawnerType { Coal, Enemy };
enum class SpawnerDirection{Up, Down, Left, Right};
class Spawner : public Object{
public:
	Spawner(Vector2 initialPos, SpawnerDirection direction, SpawnerType type, int spawnRate = 1200, int enemyCap = 20);
	void Update() override;
	void SpawnEnemy(EnemyTypes enemy, EnemyLevel level);
	void SpawnCoal();
	void Draw() override;
	SpawnerType GetType() const;
	~Spawner() override;
private:
	SpawnerType type;
	SpawnerDirection direction;
	Texture2D texture;
	Vector2 position;
	Vector2 spwnVec{};
	Rectangle activeFrame{0,0,32,32};
	int frameCounter = 0;
	int thisFrame = 0;
	int startFrame = 0;

	int spawnRate = 0;
	int spawnCounter = 0;

	int enemyCounter = 0;
	int enemyCap = 0;
	int skipFrame = 0;

	bool activated{ false };
};