#pragma once
#include "stdafx.h"
#include "Character.h"
#include "Subscriber.h"
#include "GameContentManager.h"

class Enemy :
    public Character
{
public:
    static const int SHIP_SPEED;
    static const int SHIP_WIDTH;
    static const int DEATH_VOLUME;
    static const int SHOOT_VOLUME;
    static const float SHOOT_PERCENTAGE_ANIMATION; // Enemy shoot a bullet every update where the animation state percentage is higher than this
    static const int INITIAL_HEALTH;
    static const int CANON_OFFSET;
    static const float HURT_TIME;
    static const float HURT_FLASH_TIME;

    Enemy();
    virtual void initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition) override;
    virtual bool init(const GameContentManager& contentManager);
    virtual bool uninit() override;
    virtual bool update(float deltaT) override;
    virtual void activate() override;
    virtual void shoot();
    void hit(int damage);

private:
    sf::Sound deathSound;
    sf::Sound shootSound;
};
