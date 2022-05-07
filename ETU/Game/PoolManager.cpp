#include "stdafx.h"
#include "PoolManager.h"
#include "Publisher.h"
#include <iostream>

PoolManager::PoolManager()
{
}

bool PoolManager::init(GameContentManager gameContentManager)
{
    Publisher::addSubscriber(*this, Event::PLAYER_SHOOT);
    Publisher::addSubscriber(*this, Event::ENEMY_SHOOT);

    contentManager = gameContentManager;
    initialiseObjectPool(bullets, 20, contentManager.getMainCharacterTexture()); // to const
    initialiseObjectPool(enemyBullets, 80, contentManager.getMainCharacterTexture());
    initialiseObjectPool(enemies, 20, contentManager.getEnemiesTexture());
    spawnGameObject(getAvailableGameObject(enemies), sf::Vector2f(200, 200));
    return true;
}

bool PoolManager::update(float deltaT, Player& player)
{
    updatePool(bullets, deltaT);
    updatePool(enemyBullets, deltaT);
    updatePool(enemies, deltaT);
    player.setDebugColor(sf::Color::Green);
    for (Enemy *enemy : enemies) {
        if (enemy->isActive()) {
            enemy->setDebugColor(sf::Color::Yellow);
            if (player.collidesWith(*enemy))
            {
                enemy->setDebugColor(sf::Color::Red);
                player.setDebugColor(sf::Color::Red);
            }
        }
    }

    return true;
}

void PoolManager::draw(sf::RenderWindow& window) const
{
    drawPool(bullets, window);
    drawPool(enemyBullets, window);
    drawPool(enemies, window);
}

void PoolManager::notify(Event event, const void* data)
{
    if (event == Event::PLAYER_SHOOT) {
        sf::Vector2f* pos = (sf::Vector2f*)data;
        Bullet& bullet  = getAvailableGameObject(bullets);
        spawnGameObject(bullet, *pos);
    }
    else if (event == Event::ENEMY_SHOOT) {
        sf::Vector2f* pos = (sf::Vector2f*)data;
        EnemyBullet& bullet = getAvailableGameObject(enemyBullets);
        spawnGameObject(bullet, *pos);
    }
}

bool PoolManager::uninit()
{
    deletePool(bullets);
    deletePool(enemyBullets);
    deletePool(enemies);
    return true;
}
