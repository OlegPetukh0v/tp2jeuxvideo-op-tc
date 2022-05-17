#pragma once
#include "Character.h"
#include "Healthbar.h"
class Boss :
    public Character
{
public:
    static const int BOSS_SPEED_HORIZONTAL;
    static const int BOSS_SPEED_VERTICAL;
    static const int INITIAL_HEALTH;
    static const int SPAWNING_TIME;
    static const float SPAWN_TIME;
    static const float SHOOTING_COOLDOWN;
    static const sf::Vector2f INTIAL_POSITION;
    static const float HURT_TIME;
    static const float HURT_FLASH_TIME;

    Boss();
    virtual void initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition) override;
    virtual bool init(const GameContentManager& contentManager);
    virtual bool uninit() override;
    virtual bool update(float deltaT) override;
    virtual bool update(float deltaT, sf::Vector2f targetPos);
    void updateSpawnTransition(float deltaT);
    virtual void draw(sf::RenderWindow& window) const override;
    virtual void shoot();
    void hit(int damage);

private:
    float shootingCooldown;
    float spawnCooldown;
    unsigned int shotsFired;
    sf::Vector2f targetPos;

    Healthbar healthBar;
};
