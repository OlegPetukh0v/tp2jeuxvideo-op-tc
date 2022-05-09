#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "GameContentManager.h"
class Character :
    public GameObject
{
public:
    Character(float life);

protected:
    GameContentManager contentManager;
    float life;
    float hurtTime;
};
#pragma once
