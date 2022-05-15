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
    Publisher::addSubscriber(*this, Event::ENEMY_KILLED);

    contentManager = gameContentManager;
    initialiseObjectPool(bullets, 20); // to const
    initialiseObjectPool(enemyBullets, 80);
    initialiseObjectPool(enemies, 20);
    initialiseObjectPool(healthBonuses, 5);
    return true;
}

bool PoolManager::uninit()
{
    Publisher::removeSubscriber(*this, Event::PLAYER_SHOOT);
    Publisher::removeSubscriber(*this, Event::ENEMY_SHOOT);
    Publisher::removeSubscriber(*this, Event::ENEMY_SPAWN);
    Publisher::removeSubscriber(*this, Event::ENEMY_KILLED);
    deletePool(bullets);
    deletePool(enemyBullets);
    deletePool(enemies);
    deletePool(healthBonuses);
    return true;
}

bool PoolManager::update(float deltaT, Player& player, Boss& boss)
{
    updatePool(bullets, deltaT);
    updatePool(enemyBullets, deltaT);
    updatePool(enemies, deltaT);
    updatePool(healthBonuses, deltaT);

    if (player.collidesWith(boss))
    {
        player.deactivate();
        Publisher::notifySubscribers(Event::PLAYER_DEATH, &player);
    }
    for (Bullet* bullet : enemyBullets) {
        if (bullet->isActive()) {
            if (bullet->collidesWith(player)) {
                bullet->deactivate();
                player.hit(bullet->getDamage());
            }
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
    for (Enemy* enemy : enemies) {
        if (enemy->isActive()) {
            if (player.collidesWith(*enemy))
            {
                player.hit(Character::COLLIDE_DAMAGE);
                enemy->hit(Enemy::INITIAL_HEALTH);
            }
        }
    }
    for (HealthBonus* bonus : healthBonuses) {
        if (bonus->isActive()) {
            if (bonus->collidesWith(player)) {
                bonus->deactivate();
                player.heal(HealthBonus::HEALTH);
            }
        }
    }

    return true;
}

void PoolManager::draw(sf::RenderWindow& window) const
{
    drawPool(enemyBullets, window);
    drawPool(enemies, window);
    drawPool(bullets, window);
    drawPool(healthBonuses, window);
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
        spawnGameObject(getAvailableGameObject(enemies));
    }
    else if (event == Event::ENEMY_KILLED) {
        if (rand() % 4 == 0) {
            Enemy* enemy = (Enemy*)data;
            spawnGameObject(getAvailableGameObject(healthBonuses), enemy->getPosition());
        }
    }
}
