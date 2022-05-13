#pragma once
#include "Character.h"
class Boss :
    public Character
{
public:
    static const int INITIAL_HEALTH;

private:
    float shootingCooldown;
};
