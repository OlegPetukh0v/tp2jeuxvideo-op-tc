#include "stdafx.h"
#include "PoolManager.h"
#include "Publisher.h"
#include "Game.h"
#include "EnemyType.h"
#include <iostream>

PoolManager::PoolManager()
{
}

bool PoolManager::init(GameContentManager gameContentManager)
{
    Publisher::addSubscriber(*this, Event::PLAYER_SHOOT);
    Publisher::addSubscriber(*this, Event::ENEMY_SHOOT);
    Publisher::addSubscriber(*this, Event::ENEMY_SPAWN);

    contentManager = gameContentManager;
    initialiseObjectPool(bullets, 20); // to const
    initialiseObjectPool(enemyBullets, 80);
    initialiseObjectPool(enemies, 20);
    return true;
}

bool PoolManager::uninit()
{
    Publisher::removeSubscriber(*this, Event::PLAYER_SHOOT);
    Publisher::removeSubscriber(*this, Event::ENEMY_SHOOT);
    Publisher::removeSubscriber(*this, Event::ENEMY_SPAWN);
    deletePool(bullets);
    deletePool(enemyBullets);
    deletePool(enemies);
    return true;
}

bool PoolManager::update(float deltaT, Player& player, Boss& boss)
{
    updatePool(bullets, deltaT);
    updatePool(enemyBullets, deltaT);
    updatePool(enemies, deltaT);

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
            if (bullet->collidesWith(boss))
            {
                boss.hit(bullet->getDamage());
                bullet->deactivate();
            }
        }
    }
    for (Enemy *enemy : enemies) {
        if (enemy->isActive()) {
            enemy->setDebugColor(sf::Color::Yellow);
            if (player.collidesWith(*enemy))
            {
                Publisher::notifySubscribers(Event::PLAYER_HIT, &Character::COLLIDE_DAMAGE);
                enemy->hit(Enemy::INITIAL_HEALTH);
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
    else if (event == Event::ENEMY_SPAWN) {
        //EnemyType enType = *(EnemyType*)data; // Gonna be usefull later for different enemies
        spawnGameObject(getAvailableGameObject(enemies));
    }
}
