#pragma once
#include "stdafx.h"
#include "Publisher.h"
#include "Subscriber.h"

class Spawner 
	: public Subscriber
{
public:
	static const float ENEMY_SPAWN_RATE;
	static const int ENEMY_SPAWN_CAP;
	static const int MELEE_ENEMY_SPAWN_CHANCE;
	
	Spawner();
	virtual bool init();
	virtual bool uninit();
	void update(const float deltaT);
	virtual void notify(const Event event, const void* data);

private:
	float enemySpawnRate;
	int enemySpawnCounter;
	int enemyDeathCounter;
	bool bossAvailable;

};
