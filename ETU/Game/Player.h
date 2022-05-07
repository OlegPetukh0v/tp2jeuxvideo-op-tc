#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "GameContentManager.h"
#include "Subscriber.h"
class Player :
    public GameObject
{
public:
    static const int SHIP_SPEED;
    static const float SHOOTING_COOLDOWN;

    Player();
    ~Player();
    virtual void draw(sf::RenderWindow& window) const;
    virtual void initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition);
    virtual bool init(const GameContentManager& contentManager);
    virtual bool update(float deltaT);
    virtual bool update(float deltaT, const Inputs& inputs);

private:
    GameContentManager contentManager;
    float shootingCooldown;
};
