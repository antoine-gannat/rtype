#pragma once

#define WINDOW_HEIGHT 900
#define WINDOW_WIDTH 1600

#if defined(_WIN32) || defined(WIN32)
#define PACK( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop) )
#else
#define PACK( __Declaration__ ) __Declaration__ __attribute__((__packed__))
#endif

PACK(
struct CPosition
{
  int x;
  int y;
});

PACK(
struct Position
{
  Position() {x = 0; y = 0;}
  Position(int _x, int _y) {x = _x; y = _y;}
  CPosition toC() { CPosition p; p.x = x; p.y = y; return p; }
  int x;
  int y;
});

typedef Position Size;

namespace Protocol
{
  enum EntityType
    {
      PLAYER,
      ENEMY,
      ENEMY2,
      BULLET,
      ENEMYBULLET,
      BONUS
    };

  enum EntityState
    {
      IDLE,
      DEAD
    };

  typedef unsigned int UID;

  PACK(
  struct EntityUpdate
  {
    UID id;
    EntityType type;
    EntityState state;
    Position pos;
  });

  enum PlayerKeys
  {
    UP = 0,
    DOWN,
    LEFT,
    RIGHT,
    SHOOT,
    DOWNLEFT,
    DOWNRIGHT,
    UPLEFT,
    UPRIGHT,
    NONE
  };

  PACK(
  struct PlayerUpdate
  {
    PlayerKeys key;
  });
}
