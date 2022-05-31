#pragma once
#include "stdafx.h"
#include "GameContentManager.h"
#include "Bullet.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "Subscriber.h"
#include "Player.h"
#include "Boss.h"
#include "HealthBonus.h"
#include "AttackBonus.h"
#include "MeleeEnemy.h"

class PoolManager 
	: public Subscriber
{
	static const int BONUS_SPAWN_CHANCE;
	static const int HEALTH_BONUS_SPAWN_CHANCE;
	static const unsigned int INITIAL_NB_BULLETS;
	static const unsigned int INITIAL_NB_ENEMY_BULLETS;
	static const unsigned int INITIAL_NB_ENEMY;
	static const unsigned int INITIAL_NB_HEALTH_BONUS;
	static const unsigned int INITIAL_NB_ATTACK_BONUS;

public:
	PoolManager();

	bool init(GameContentManager contentManager);

	bool uninit();

	bool update(const float deltaT, Player& player, Boss& boss);

	void draw(sf::RenderWindow& window) const;

	virtual void notify(Event event, const void* data);

	template<class T>
	void initialiseObjectPool(std::list<T*>& poolT, const int initialSize);

	template<class T>
	T& getAvailableGameObject(std::list<T*>& poolT);

	template<class T>
	void spawnGameObject(T& objT, sf::Vector2f pos = sf::Vector2f(0, 0));

	template<class T>
	void updatePool(std::list<T*>& poolT, const float deltaT);

	template<class T>
	void drawPool(std::list<T*> poolT, sf::RenderWindow& window) const;
	
	template<class T>
	void deletePool(std::list<T*>& poolT);
private:
	MeleeEnemy meleeEnemy;
	GameContentManager contentManager;
	std::list<Bullet*> bullets;
	std::list<EnemyBullet*> enemyBullets;
	std::list<Enemy*> enemies;
	std::list<MeleeEnemy*> meleeEnemies;
	std::list<HealthBonus*> healthBonuses;
	std::list<AttackBonus*> attackBonuses;
};

template<class T>
inline void PoolManager::initialiseObjectPool(std::list<T*>& poolT, const int initialSize)
{
	for (unsigned short i = 0; i < initialSize; i++) {
		T* temp = new T();
		temp->init(contentManager);
		poolT.push_back(temp);
	}
}

template<class T>
inline T& PoolManager::getAvailableGameObject(std::list<T*>& poolT)
{
	for (T* temp : poolT) {
		if (!temp->isActive()) {
			return *temp;
		}
	}
	T* temp = new T();
	temp->init(contentManager);
	poolT.push_back(temp);
	return *poolT.back();
}

template<class T>
inline void PoolManager::spawnGameObject(T& objT, sf::Vector2f pos)
{
	objT.setPosition(pos);
	objT.activate();
}

template<class T>
inline void PoolManager::updatePool(std::list<T*>& poolT, const float deltaT)
{
	for (T* temp : poolT) {
		if (temp->isActive()) {
			temp->update(deltaT);
		}
	}
}

template<class T>
inline void PoolManager::drawPool(std::list<T*> poolT, sf::RenderWindow& window) const
{
	for (T* temp : poolT) {
		if (temp->isActive()) {
			temp->draw(window);
		}
	}
}

template<class T>
inline void PoolManager::deletePool(std::list<T*>& poolT)
{
	for (T* temp : poolT) {
		delete temp;
	}
	poolT.clear();
}
