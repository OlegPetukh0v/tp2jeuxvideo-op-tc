#pragma once
#include "Character.h"
#include "Healthbar.h"
class Boss :
    public Character
{
public:
    static const int BOSS_SPEED;
    static const int INITIAL_HEALTH;
    static const int SPAWNING_TIME;

    Boss();
    virtual bool init(const GameContentManager& contentManager);
    virtual bool uninit() override;
    virtual bool update(float deltaT) override;
    virtual void draw(sf::RenderWindow& window) const override;
    virtual void shoot();

private:
    float shootingCooldown;
    unsigned int shotsFired;

    Healthbar healthBar;
};
