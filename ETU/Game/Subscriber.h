#pragma once
#include "event.h"
struct Subscriber
{
  // La seule m�thode de l'interface
  virtual void notify(const Event event, const void* data)=0;
};
