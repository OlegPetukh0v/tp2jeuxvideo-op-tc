#pragma once
#include "Animation.h"

class CyclicAnimation :
  public Animation
{
public:
  virtual void update(const float deltaT, const Inputs& inputs) override;
  virtual unsigned int getNextFrame() const override;
  float getPercentage() const override;

protected:
  CyclicAnimation(sf::Sprite& s, const float length, const bool repeated = false);

private:
  float timeOrientation;
  bool repeated;

};
