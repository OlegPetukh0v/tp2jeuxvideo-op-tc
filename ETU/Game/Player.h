#pragma once
#include "stdafx.h"
#include "Character.h"
#include "GameContentManager.h"
#include "ShipAnimation.h"
#include "AnimatedGameObject.h"
#include "Subscriber.h"
class Player :
    public Character, public Subscriber
{
public:
    static const int SHIP_SPEED;
    static const float SHOOTING_COOLDOWN;
    static const int CANON_OFFSET;
    static const int INITIAL_LIFE;
    static const float HURT_TIME;

    Player();
    ~Player();
    virtual void draw(sf::RenderWindow& window) const;
    virtual void initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition);
    virtual bool init(const GameContentManager& contentManager);
    virtual bool update(float deltaT, const Inputs& inputs);
    void notify(Event event, const void* data);
    bool isAlive();
private:
    float shootingCooldown;
};
