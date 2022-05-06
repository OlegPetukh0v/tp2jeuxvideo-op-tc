#include "stdafx.h"
#include "Player.h"

const int Player::SHIP_SPEED = 5;

Player::Player()
{
}

Player::~Player()
{
}

void Player::draw(sf::RenderWindow& window) const
{
	window.draw(*this);
}

void Player::initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition)
{
	setTexture(texture);
	setTextureRect(sf::IntRect(269, 47, 26, 29));
	setScale(2, 2);
	setPosition(initialPosition);
}

bool Player::init(const GameContentManager& contentManager)
{
	this->contentManager = contentManager;
	this->initialize(contentManager.getMainCharacterTexture(), sf::Vector2f(100,100));
	return true;
}

bool Player::update(float deltaT)
{
	return false;
}

bool Player::update(float deltaT, const Inputs& inputs)
{
	sf::Vector2f direction;
}
