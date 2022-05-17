#pragma once
#include "Animation.h"
class LinearAnimation :
    public Animation
{
public:
  virtual void update(const float deltaT, const Inputs& inputs) override;
  virtual unsigned int getNextFrame() const override;
  virtual float getPercentage() const override;

protected:
  LinearAnimation(sf::Sprite& s, const float length, const bool repeated = false);

private:
  bool repeated;

};
