#pragma once
#include "stdafx.h"
#include "GameContentManager.h"
#include "Bullet.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "Subscriber.h"
#include <iostream>

class PoolManager : public Subscriber
{
public:
	PoolManager();

	bool init(GameContentManager contentManager);

	bool update(float deltaT);

	void draw(sf::RenderWindow& window) const;

	virtual void notify(Event event, const void* data);

	bool uninit();

	template<class T>
	void initialiseObjectPool(std::list<T*>& poolT, int initialSize, const sf::Texture& texture);

	template<class T>
	T& getAvailableGameObject(std::list<T*> poolT);

	template<class T>
	void spawnGameObject(T& enemy, sf::Vector2f pos);

	template<class T>
	void updatePool(std::list<T*> poolT, float deltaT);

	template<class T>
	void drawPool(std::list<T*> poolT, sf::RenderWindow& window) const;
	
	template<class T>
	void deletePool(std::list<T*>& poolT);
private:
	GameContentManager contentManager;
	std::list<Bullet*> bullets;
	std::list<EnemyBullet*> enemyBullets;
	std::list<Enemy*> enemies;
};

	template<class T>
	inline void PoolManager::initialiseObjectPool(std::list<T*>& poolT, int initialSize, const sf::Texture& texture)
	{
		for (unsigned short i = 0; i < initialSize; i++) {
			T* temp = new T();
			temp->initialize(texture, sf::Vector2f(0,0));
			poolT.push_back(temp);
		}
	}

	template<class T>
	inline T& PoolManager::getAvailableGameObject(std::list<T*> poolT)
	{
		for (T* temp : poolT) {
			if (!temp->isActive()) {
				return *temp;
			}
		}
		T* temp = new T();
		temp->initialize(contentManager.getMainCharacterTexture(), sf::Vector2f(0,0));
		poolT.push_back(temp);
		return *poolT.back(); // FIXME : Le return et le push_back() ne fonctionnent pas...
	}

	template<class T>
	inline void PoolManager::spawnGameObject(T& objT, sf::Vector2f pos)
	{
		objT.activate();
		objT.setPosition(pos);
	}

	template<class T>
	inline void PoolManager::updatePool(std::list<T*> poolT, float deltaT)
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
	}
