#if defined(_WIN32) || defined(WIN32)
#include <Windows.h>
#define _USE_MATH_DEFINES
#endif
#include <cmath>
#include "Protocol.hpp"

extern "C"
#if defined(_WIN32) || defined(WIN32)
__declspec( dllexport )
#endif
CPosition pattern(CPosition pos, int speed, CPosition *target)
{
  pos.x -= speed;
  float xpi = ((float)pos.x / (float)WINDOW_WIDTH) * 4.0 * M_PI;
  pos.y = target->y + (200.0 * sin(xpi));
  if (pos.x <= 0)
    pos.x = WINDOW_WIDTH;
  return (pos);
}
