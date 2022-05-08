#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "Subscriber.h"
#include "GameContentManager.h"
#include <iostream>
class Enemy :
    public GameObject
{
public:
    static const int SHIP_SPEED;
    static const int INITIAL_HEALTH;
    static const float SHOOTING_COOLDOWN;
    static const float HURT_TIME;

    Enemy();
    virtual void initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition) override;
    virtual bool init(const GameContentManager& contentManager);
    virtual bool update(float deltaT) override;
    virtual void activate() override;
    void hit(int damage);

private:
    GameContentManager contentManager;
    float shootingCooldown;
    float health;
    float hurtTime;
};
