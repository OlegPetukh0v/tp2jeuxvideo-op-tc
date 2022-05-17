#include "stdafx.h"
#include "Spawner.h"
#include "EnemyType.h"

const float Spawner::ENEMY_SPAWN_RATE = 1.5f;
const int Spawner::ENEMY_SPAWN_CAP = 30;

Spawner::Spawner()
{
    enemySpawnRate = ENEMY_SPAWN_RATE;
    enemySpawnCounter = 0;
    enemyDeathCounter = 0;
    bossAvailable = true;
}

bool Spawner::init()
{
    Publisher::addSubscriber(*this, Event::ENEMY_KILLED);
    return true;
}

bool Spawner::uninit()
{
    Publisher::removeSubscriber(*this, Event::ENEMY_KILLED);
    return true;
}

void Spawner::update(float deltaT)
{

    if (enemySpawnCounter < ENEMY_SPAWN_CAP) {
        enemySpawnRate -= deltaT;
        if (enemySpawnRate <= 0) {
            int enumId = (int)EnemyType::SMALL_SHIP;
            Publisher::notifySubscribers(Event::ENEMY_SPAWN, &enumId);
            float randomTime = ((rand() % 10) / 10) - 0.5f;
            enemySpawnRate = ENEMY_SPAWN_RATE + randomTime;
            enemySpawnCounter++;
        }
    }
    else if (bossAvailable && enemyDeathCounter >= ENEMY_SPAWN_CAP){
        Publisher::notifySubscribers(Event::BOSS_SPAWN, NULL);
        bossAvailable = false;
    }
    
}

void Spawner::notify(Event event, const void* data)
{
    if (event == Event::ENEMY_KILLED)
    {
        enemyDeathCounter++;
    }
}
