#include "stdafx.h"
#include "Spawner.h"
#include "EnemyType.h"

const float Spawner::ENEMY_SPAWN_RATE = 2.0f;
const int Spawner::ENEMY_SPAWN_CAP = 25;

Spawner::Spawner()
{
    enemySpawnRate = ENEMY_SPAWN_RATE;
    enemySpawnCounter = 0;
    bossAvailable = true;
}

void Spawner::update(float deltaT)
{
    enemySpawnRate -= deltaT;

    if (enemySpawnCounter < ENEMY_SPAWN_CAP) {
        if (enemySpawnRate <= 0) {
            int enumId = (int)EnemyType::SMALL_SHIP;
            Publisher::notifySubscribers(Event::ENEMY_SPAWN, &enumId);
            float randomTime = ((rand() % 10) / 10) - 0.5f;
            enemySpawnRate = ENEMY_SPAWN_RATE + randomTime;
            enemySpawnCounter++;
        }
    }
    else if (bossAvailable){
        Publisher::notifySubscribers(Event::BOSS_SPAWN, NULL);
        bossAvailable = false;
    }
    
}
