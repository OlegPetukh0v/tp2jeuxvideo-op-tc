#include "stdafx.h"
#include "Character.h"

const int Character::COLLIDE_DAMAGE = 10;

Character::Character(const int life)
{
	hurtTime = 0;
	this->health = life;
}

int Character::getHealth() const 
{
	return this->health;
}

bool Character::uninit() 
{
	return true;
}
