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
    static const int SHOOTING_VOLUME;
    static const int CANON_OFFSET;
    static const int BONUS_CANON_OFFSET;
    static const int INITIAL_HEALTH;
    static const float HURT_TIME;
    static const unsigned int SCORE_INCREASE_KILL;
    static const unsigned int BONUS_TIME;

    Player();
    ~Player();
    virtual void draw(sf::RenderWindow& window) const;
    virtual void initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition);
    virtual bool init(const GameContentManager& contentManager);
    virtual bool uninit() override;
    virtual bool update(float deltaT, const Inputs& inputs);
    void hit(int damage);
    void heal(int health);
    void notify(Event event, const void* data);
    bool isAlive();
    unsigned int getScore();
    void activateBonus();
    bool hasBonus();

private:
    float shootingCooldown;
    unsigned int score;
    sf::Sound shootSound;
    float bonusTime;
};
