#include "stdafx.h"
#include "PoolManager.h"
#include "Publisher.h"
#include "Player.h"
#include <iostream>

PoolManager::PoolManager()
{
}

bool PoolManager::init(GameContentManager gameContentManager)
{
    contentManager = gameContentManager;
    initialiseObjectPool(poolBullets, 20, contentManager.getMainCharacterTexture()); // to const
    return true;
}

bool PoolManager::update(float deltaT)
{
    for (Bullet* bullet : poolBullets) {
        bullet->update(deltaT);
    }
    return true;
}

void PoolManager::draw(sf::RenderWindow& window) const
{
    int count = 0;
    for(Bullet * bullet : poolBullets) {
        if (bullet->isActive()) {
            count++;
            bullet->draw(window);
        }
   }
    if(count > 0) std::cout << count << " bullet" << std::endl;
}

void PoolManager::notify(Event event, const void* data)
{
    if (event == Event::PLAYER_SHOOT) {
        Player* player = (Player*)data;
        Bullet& bullet  = getAvailableGameObject(poolBullets);
        spawnGameObject(bullet, player->getPosition());
    }
}

bool PoolManager::uninit()
{
    std::cout << poolBullets.size() << std::endl;
    deletePool(poolBullets);
    return true;
}
