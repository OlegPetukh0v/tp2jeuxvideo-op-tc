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
    virtual bool update(const float deltaT, const Inputs& inputs);
    void notify(const Event event, const void* data);

    void activateBonus();
    void hit(const int damage);
    void heal(const int health);

    bool hasBonus() const;
    bool isAlive() const;

    unsigned int getScore() const;
    unsigned int getBonusTime() const;

private:
    float shootingCooldown;
    unsigned int score;
    sf::Sound shootSound;
    float bonusTime;

};
