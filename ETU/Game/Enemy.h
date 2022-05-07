#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "GameContentManager.h"
class Enemy :
    public GameObject
{
public:
    static const int SHIP_SPEED;
    static const float SHOOTING_COOLDOWN;

    Enemy();
    virtual void initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition);
    virtual bool init(const GameContentManager& contentManager);
    virtual bool update(float deltaT);

private:
    GameContentManager contentManager;
    float shootingCooldown;
};
