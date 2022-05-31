#include "stdafx.h"
#include "Spawner.h"
#include <iostream>

const float Spawner::ENEMY_SPAWN_RATE = 2.0f;
const int Spawner::ENEMY_SPAWN_CAP = 30;
const int Spawner::MELEE_ENEMY_SPAWN_CHANCE = 4; // -1 = Never. 0 = Always. Higher number will results in lower chance

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

void Spawner::update(const float deltaT)
{
    if (enemySpawnCounter < ENEMY_SPAWN_CAP) {
        enemySpawnRate -= deltaT;
        if (enemySpawnRate <= 0) {
            if (rand() % MELEE_ENEMY_SPAWN_CHANCE == 0) Publisher::notifySubscribers(Event::MELEE_ENEMY_SPAWN, nullptr);
            else {
                Publisher::notifySubscribers(Event::ENEMY_SPAWN, nullptr);
            }
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

void Spawner::notify(const Event event, const void* data)
{
    if (event == Event::ENEMY_KILLED)
    {
        enemyDeathCounter++;
    }
}
