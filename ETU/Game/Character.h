#pragma once
#include "stdafx.h"
#include "AnimatedGameObject.h"
#include "GameContentManager.h"
class Character :
    public AnimatedGameObject
{
public:
    Character(float life);

protected:
    GameContentManager contentManager;
    float health;
    float hurtTime;
};
#pragma once
