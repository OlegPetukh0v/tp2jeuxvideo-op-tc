#include "stdafx.h"
#include "Spawner.h"
#include "EnemyType.h"

const float Spawner::ENEMY_SPAWN_TIME = 2.0f;

void Spawner::update(float deltaT)
{
	enemySpawnTime -= deltaT;

    if (enemySpawnTime <= 0) {
        int enumId = (int)EnemyType::SMALL_SHIP;
        Publisher::notifySubscribers(Event::ENEMY_SPAWN, &enumId);
        float randomTime = ((rand() % 10) / 10) - 0.5f;
        enemySpawnTime = ENEMY_SPAWN_TIME + randomTime;
    }
}
