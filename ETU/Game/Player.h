#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "GameContentManager.h"
#include "Subscriber.h"
class Player :
    public GameObject, public Subscriber
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

private:
    GameContentManager contentManager;
    float shootingCooldown;
    float life;
    bool shootLeft;
    float hurtTime;
};
