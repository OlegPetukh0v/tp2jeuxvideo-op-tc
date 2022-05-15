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
    static const float HURT_TIME;
    static const sf::Vector2f INTIAL_POSITION;

    Boss();
    virtual void initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition) override;
    virtual bool init(const GameContentManager& contentManager);
    virtual bool uninit() override;
    virtual bool update(float deltaT) override;
    virtual bool update(float deltaT, sf::Vector2f targetPos);
    virtual void draw(sf::RenderWindow& window) const override;
    virtual void shoot();
    void hit(int damage);

private:
    float shootingCooldown;
    unsigned int shotsFired;
    sf::Vector2f targetPos;

    Healthbar healthBar;
};
