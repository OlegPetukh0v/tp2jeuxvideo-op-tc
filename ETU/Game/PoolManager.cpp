#include "stdafx.h"
#include "PoolManager.h"
#include "Publisher.h"
#include "Game.h"
#include "EnemyType.h"
#include <iostream>

const int PoolManager::BONUS_SPAWN_CHANCE = 4;
const int PoolManager::HEALTH_BONUS_SPAWN_CHANCE = 2;
const unsigned int PoolManager::INITIAL_NB_BULLETS = 30;
const unsigned int PoolManager::INITIAL_NB_ENEMY_BULLETS = 80;
const unsigned int PoolManager::INITIAL_NB_ENEMY = 30;
const unsigned int PoolManager::INITIAL_NB_HEALTH_BONUS = 5;
const unsigned int PoolManager::INITIAL_NB_ATTACK_BONUS = 5;

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
    initialiseObjectPool(bullets, INITIAL_NB_BULLETS);
    initialiseObjectPool(enemyBullets, INITIAL_NB_ENEMY_BULLETS);
    initialiseObjectPool(enemies, INITIAL_NB_ENEMY);
    initialiseObjectPool(healthBonuses, INITIAL_NB_HEALTH_BONUS);
    initialiseObjectPool(attackBonuses, INITIAL_NB_ATTACK_BONUS);
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
    deletePool(attackBonuses);
    return true;
}

bool PoolManager::update(const float deltaT, Player& player, Boss& boss)
{
    updatePool(bullets, deltaT);
    updatePool(enemyBullets, deltaT);
    updatePool(enemies, deltaT);
    updatePool(healthBonuses, deltaT);
    updatePool(attackBonuses, deltaT);

    if (player.collidesWith(boss))
    {
        player.deactivate();
        Publisher::notifySubscribers(Event::PLAYER_DEATH, &player);
    }
    for (Bullet* bullet : enemyBullets) {
        if (bullet->isActive()) {
            if (bullet->collidesWith(player)) {
                player.hit(bullet->getDamage());
                bullet->deactivate();
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
                bonus->onPick(player);
            }
        }
    }
    for (AttackBonus* bonus : attackBonuses) {
        if (bonus->isActive()) {
            if (bonus->collidesWith(player)) {
                bonus->onPick(player);
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
    drawPool(attackBonuses, window);
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
        if (rand() % BONUS_SPAWN_CHANCE == 0) {
            Enemy* enemy = (Enemy*)data;
            if (rand() % HEALTH_BONUS_SPAWN_CHANCE == 0)
                spawnGameObject(getAvailableGameObject(healthBonuses), enemy->getPosition());            
            else
                spawnGameObject(getAvailableGameObject(attackBonuses), enemy->getPosition());            
        }
    }
}
