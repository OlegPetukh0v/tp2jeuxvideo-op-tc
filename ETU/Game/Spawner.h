#pragma once
#include "stdafx.h"
#include "Publisher.h"

class Spawner
{
public:
	static const float ENEMY_SPAWN_TIME;

	void update(float deltaT);
private:
	float enemySpawnTime;
};