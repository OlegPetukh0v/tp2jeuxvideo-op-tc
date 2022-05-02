#include "stdafx.h"
#include "TitleScene.h"

#include "game.h"

TitleScene::TitleScene()
  : Scene(SceneType::TITLE_SCENE)
{

}

TitleScene::~TitleScene()
{

}
SceneType TitleScene::update()
{
  return getSceneType();
}

void TitleScene::draw(sf::RenderWindow& window) const
{
  window.draw(menuImage);
  window.draw(pressKeyMessage);
}

bool TitleScene::init()
{
  if (false == contentManager.loadContent())
    return false;
  menuImage.setTexture(contentManager.getBackgroundTexture());
  menuImage.setOrigin(menuImage.getTexture()->getSize().x / 2.0f, menuImage.getTexture()->getSize().y / 2.0f);
  menuImage.setPosition(Game::GAME_WIDTH / 2.0f, Game::GAME_HEIGHT / 2.0f);

  pressKeyMessage.setFont(contentManager.getMainFont());
  pressKeyMessage.setCharacterSize(24);
  pressKeyMessage.setFillColor(sf::Color::White);
  pressKeyMessage.setString("PRESS ANY KEY TO START"); // TO CONST
  pressKeyMessage.setOrigin(pressKeyMessage.getLocalBounds().width / 2.0f, pressKeyMessage.getLocalBounds().height / 2.0f);
  pressKeyMessage.setPosition(Game::GAME_WIDTH / 2.0f, Game::GAME_HEIGHT / 1.25f);

  return true;
}

bool TitleScene::uninit()
{
  return true;
}

bool TitleScene::handleEvents(sf::RenderWindow& window)
{
  bool retval = false;
  sf::Event event;
  while (window.pollEvent(event))
  {
    //x sur la fenêtre
    if (event.type == sf::Event::Closed)
    {
      window.close();
      retval = true;
    }
  }
  return retval;

}
