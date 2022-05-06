#pragma once
#include "stdafx.h"

class PoolManager
{
public:
	template<class T>
	void initialiseObjectPool(std::list<T*>& poolT, int initialSize);

	template<class T>
	T& getAvailableGameObject(std::list<T*> poolT);

	template<class T>
	void spawnGameObject(T& enemy, sf::Vector2f pos);

	template<class T>
	void deletePool(std::list<T*>& poolT);
};

	template<class T>
	inline void PoolManager::initialiseObjectPool(std::list<T*>& poolT, int initialSize)
	{
		for (unsigned short i = 0; i < initialSize; i++) {
			T* temp = new T();
			temp->initialize();
			poolT.push_back(temp);
		}
	}

	template<class T>
	inline T& PoolManager::getAvailableGameObject(std::list<T*> poolT)
	{
		for (T* temp : poolT) {
			if (!temp->isActive()) {
				temp->activate();
				return *temp;
			}
		}
		T* temp = new T();
		temp->initialize();
		poolT.push_back(temp);
		return *poolT.back();
	}

	template<class T>
	inline void PoolManager::spawnGameObject(T& objT, sf::Vector2f pos)
	{
		objT.activate();
		objT.setPosition(pos);
	}

	template<class T>
	inline void PoolManager::deletePool(std::list<T*>& poolT)
	{
		for (T* objT : poolT) {
			delete objT;
		}
	}
