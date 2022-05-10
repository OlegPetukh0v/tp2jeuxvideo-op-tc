#pragma once
#include "GameObject.h"
#include "GameContentManager.h"
#include "AnimationState.h"

class ContentManager;
class Animation;
struct Inputs;
class AnimatedGameObject :
    public GameObject
{
public:
  AnimatedGameObject();
  virtual ~AnimatedGameObject();
  AnimatedGameObject(const AnimatedGameObject& src);

  virtual bool update(float deltaT, const Inputs& inputs) ;
  virtual void draw(sf::RenderWindow& window) const override;
  virtual bool init(const ContentManager& contentManager);

protected:
  State currentState;
  std::map<State, Animation*> animations;
  ContentManager* contentManager;

  template<State state, class AnimationType >
  bool addAnimation(const GameContentManager& contentManager)
  {
      Animation* animation = new AnimationType(*this);
      bool retval = animation->init(contentManager);
      if (retval)
          animations[state] = animation;
      return retval;
  }
private:
  AnimatedGameObject& operator=(const AnimatedGameObject&);

  
};

