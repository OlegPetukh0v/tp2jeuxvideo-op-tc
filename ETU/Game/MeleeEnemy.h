#pragma once
#include "stdafx.h"
#include "Character.h"
#include "Subscriber.h"
#include "GameContentManager.h"

class MeleeEnemy :
    public Character
{
public:
    static const int MONSTER_SPEED;
    static const int DEATH_VOLUME;
    static const int INITIAL_HEALTH;
    static const float HURT_TIME;
    static const float HURT_FLASH_TIME;

    MeleeEnemy();
    virtual void initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition) override;
    virtual bool init(const GameContentManager& contentManager);
    virtual bool uninit() override;
    virtual bool update(const float deltaT) override;
    virtual void activate() override;
    virtual void charge();
    void hit(const int damage);

private:
    sf::Sound deathSound;
    bool goingLeft;
};
