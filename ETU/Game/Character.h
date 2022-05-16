#pragma once
#include "stdafx.h"
#include "AnimatedGameObject.h"
#include "GameContentManager.h"
class Character :
    public AnimatedGameObject
{
public:
    static const int COLLIDE_DAMAGE;
    Character(int health);
    int getHealth() const;
    virtual bool uninit();

protected:
    GameContentManager contentManager;
    int health;
    float hurtTime;
};
#pragma once
