#pragma once
#include "event.h"
struct Subscriber
{
  // La seule méthode de l'interface
  virtual void notify(const Event event, const void* data)=0;
};
