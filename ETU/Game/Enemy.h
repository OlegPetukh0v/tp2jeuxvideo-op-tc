#pragma once
#include "stdafx.h"
#include "Character.h"
#include "Subscriber.h"
#include "GameContentManager.h"
#include <iostream>
class Enemy :
    public Character
{
public:
    static const int SHIP_SPEED;
    static const int INITIAL_HEALTH;
    static const float HURT_TIME;

    Enemy();
    virtual void initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition) override;
    virtual bool init(const GameContentManager& contentManager);
    virtual bool update(float deltaT) override;
    virtual void activate() override;
    void hit(int damage);

private:
    float shootingCooldown;
};
