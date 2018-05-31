#if defined(_WIN32) || defined(WIN32)
#include <Windows.h>
#endif
#include <math.h>
#include <stdlib.h>
#include "Protocol.hpp"

static double calcDist(CPosition pos1, CPosition pos2)
{
  return (sqrt(pow(pos2.y - pos1.y, 2) + pow(pos2.x - pos1.x,2)));
}

extern "C"
#if defined(_WIN32) || defined(WIN32)
__declspec( dllexport )
#endif
CPosition pattern(CPosition pos, int speed, CPosition *target)
{
  if (calcDist(pos, *target) < 50)
  {
    if (pos.x > 0 && pos.y > 0)
    {
      target->x = pos.x - (rand() % 200);
      target->y = rand() % WINDOW_HEIGHT;
    }
    else
    {
      target->x = -10;
      target->y = 50;
    }
  }
  if (target->y > pos.y)
  {
    pos.y += speed;
  }
  else
  {
    pos.y -= speed;
  }
  pos.x -= speed;
  if (pos.x <= 0)
  {
    pos.x = WINDOW_WIDTH;
  }
  return (pos);
}
