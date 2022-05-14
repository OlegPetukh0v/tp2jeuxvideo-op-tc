#pragma once
#include "Character.h"
#include "Healthbar.h"
class Boss :
    public Character
{
public:
    static const int BOSS_SPEED;
    static const int INITIAL_HEALTH;

    virtual bool init(const GameContentManager& contentManager);
    virtual void draw(sf::RenderWindow& window) const override;

private:
    float shootingCooldown;
    unsigned int shotsFired;

    Healthbar healthBar;
};
