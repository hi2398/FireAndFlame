#include "Spawner.h"

Spawner::Spawner(Vector2 initialPos, SpawnerDirection direction, SpawnerType type, int spawnRate, int enemyCounter) : Object(ObjectTypes::other)
{
	this->position = initialPos;
	this->type = type;
	this->direction = direction;
	this->spawnRate = spawnRate;
	this->enemyCap = enemyCounter;
	texture = LoadTexture("assets/graphics/OtherObjects/SpawnerSheet.png");
	switch (direction)
	{
	case SpawnerDirection::Up:
		if (type == SpawnerType::Enemy) {
			startFrame = 0;
			thisFrame = startFrame;
			spwnVec = { position.x, position.y };
		}
		else {
			startFrame = 0;
			thisFrame = startFrame;
			spwnVec = { position.x + 5, position.y - 32 };
		}
		
		break;
	case SpawnerDirection::Down:
		if (type == SpawnerType::Enemy) {
			startFrame = 3;
			thisFrame = startFrame;
		}
		else {
			startFrame = 0;
			thisFrame = startFrame;
		}
		
		spwnVec = { position.x + 5, position.y + 32 };
		break;
	case SpawnerDirection::Left:
		if (type == SpawnerType::Enemy) {
			startFrame = 0;
			thisFrame = startFrame;
			spwnVec = { position.x, position.y };
		}
		else {
			startFrame = 3;
			thisFrame = startFrame;
			spwnVec = { position.x - 32, position.y };
		}
		
		break;
	case SpawnerDirection::Right:
		if (type == SpawnerType::Enemy) {
			startFrame = 0;
			thisFrame = startFrame;
		}
		else {
			startFrame = 3;
			thisFrame = startFrame;
		}
		spwnVec = { position.x + 32, position.y };
		break;
	default:
		break;
	}

	if (type == SpawnerType::Enemy) spawnRate = 600;
}

void Spawner::Update()
{
	if (activated) {
		frameCounter++;
		if (frameCounter >= 10) {
			thisFrame++;
			frameCounter = 0;
		}
	}
	if (thisFrame == startFrame + 3) thisFrame = startFrame, activated = false;

	if (type == SpawnerType::Enemy && (direction == SpawnerDirection::Left|| direction == SpawnerDirection::Right)) {
		activeFrame.x = (float)64 * thisFrame;
	}
	else {
		activeFrame.x = (float)32 * thisFrame;
	}
	


	switch (type)
	{
	case SpawnerType::Coal:
		switch (direction)
		{
		case SpawnerDirection::Down:
			activeFrame.y = 32;
			break;
		case SpawnerDirection::Left:
			activeFrame.y = 32;
			break;
		default:
			break;
		}
		break;
	case SpawnerType::Enemy:
		switch (direction)
		{
		case SpawnerDirection::Up:
			activeFrame.y = 32 * 2;
			activeFrame.height = 64;
			break;
		case SpawnerDirection::Down:
			activeFrame.y = 32 * 2;
			activeFrame.height = 64;
			break;
		case SpawnerDirection::Left:
			activeFrame.y = 32 * 5;
			activeFrame.width = 64;
			break;
		case SpawnerDirection::Right:
			activeFrame.y = 32 * 4;
			activeFrame.width = 64;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	for (const auto& enemy : sceneManager->GetEnemies()) {
		enemyCounter++;
	}
	if (enemyCounter <= enemyCap / 2 && type == SpawnerType::Enemy) spawnRate = 300;
	else if (enemyCounter > enemyCap / 2 && type == SpawnerType::Enemy)spawnRate = 600;
}

void Spawner::SpawnEnemy(EnemyTypes enemy, EnemyLevel level)
{
	spawnCounter++;
	if (spawnCounter >= spawnRate) {
		activated = true; //activate frame handling when spawning entity
		skipFrame++;
		if (skipFrame >= 25) {
			skipFrame = 0;
			spawnCounter = 0;

			
			switch (enemy)
			{
			case EnemyTypes::ToastCat:
				sceneManager->AddEnemy(std::make_unique<ToastCat>(spwnVec));
				break;
			case EnemyTypes::Miner:
				sceneManager->AddEnemy(std::make_unique<Miner>(spwnVec, level));
				break;
			case EnemyTypes::SpiderBot:
				sceneManager->AddEnemy(std::make_unique<SpiderBot>(spwnVec, level));
				break;
			case EnemyTypes::Flyer:
				sceneManager->AddEnemy(std::make_unique<Fly>(spwnVec, level));
				break;
			case EnemyTypes::SpringHog:
				sceneManager->AddEnemy(std::make_unique<Howler>(spwnVec, level));
				break;
			case EnemyTypes::Howler:
				sceneManager->AddEnemy(std::make_unique<SpringHog>(spwnVec, level));
				break;
			case EnemyTypes::Saugi:
				sceneManager->AddEnemy(std::make_unique<Saugi>(spwnVec));
				break;
			default:
				break;
			}
		}
	}
}

void Spawner::SpawnCoal()
{
	spawnCounter++;
	if (spawnCounter >= spawnRate) {
		activated = true;
		spawnCounter = 0;
		sceneManager->AddInteractable(std::make_unique<Coal>(spwnVec));
	}
}

void Spawner::Draw()
{
	DrawTextureRec(texture, activeFrame, position, WHITE);
}

SpawnerType Spawner::GetType() const
{
	return type;
}

Spawner::~Spawner()
{
	UnloadTexture(texture);
}
