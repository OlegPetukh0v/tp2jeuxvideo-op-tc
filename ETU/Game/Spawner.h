#pragma once
#include "stdafx.h"
#include "Publisher.h"

class Spawner
{
public:
	static const float ENEMY_SPAWN_RATE;
	static const int ENEMY_SPAWN_CAP;
	
	Spawner();
	void update(float deltaT);
private:
	int enemySpawnRate;
	int enemySpawnCounter;
	bool bossAvailable;
};