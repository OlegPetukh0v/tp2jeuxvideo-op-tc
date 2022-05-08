#include "stdafx.h"
#include "PoolManager.h"
#include "Publisher.h"
#include "Game.h"
#include <iostream>

const int PoolManager::ENEMY_SPAWN_TIME = 2;

PoolManager::PoolManager()
{
    enemySpawnTime = ENEMY_SPAWN_TIME;
}

bool PoolManager::init(GameContentManager gameContentManager)
{
    Publisher::addSubscriber(*this, Event::PLAYER_SHOOT);
    Publisher::addSubscriber(*this, Event::ENEMY_SHOOT);

    contentManager = gameContentManager;
    initialiseObjectPool(bullets, 20, contentManager.getMainCharacterTexture()); // to const
    initialiseObjectPool(enemyBullets, 80, contentManager.getMainCharacterTexture());
    initialiseObjectPool(enemies, 20, contentManager.getEnemiesTexture());
    return true;
}

bool PoolManager::update(float deltaT, Player& player)
{
    enemySpawnTime -= deltaT;
    updatePool(bullets, deltaT);
    updatePool(enemyBullets, deltaT);
    updatePool(enemies, deltaT);
    player.setDebugColor(sf::Color::Green);

    if (enemySpawnTime <= 0) {
        float randomTime = ((rand() % 10) / 10) - 0.5f;
        enemySpawnTime = ENEMY_SPAWN_TIME + randomTime;
        float x = rand() % (Game::GAME_WIDTH - 40);
        spawnGameObject(getAvailableGameObject(enemies), sf::Vector2f(x + 20, -50));
    }

    for (Bullet* bullet : enemyBullets) {
        if (bullet->isActive()) {
            if(bullet->collidesWith(player)) bullet->deactivate();
        }
    }
    for (Bullet* bullet : bullets) {
        if (bullet->isActive()) {
            for (Enemy* enemy : enemies) {
                if (enemy->isActive()) {
                    if (bullet->collidesWith(*enemy)) {
                        enemy->hit(bullet->getDamage());
                        bullet->deactivate();
                    }
                }
            }
        }
    }
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
