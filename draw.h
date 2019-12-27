#include "BATTLE_API.h"

#ifndef DRAW_H
#define DRAW_H

#include <array>
#include "Army.h"

class Battle;

extern "C" BATTLE_API void draw(const Battle&);
extern "C" BATTLE_API void draw_winner(const Battle&);
extern "C" BATTLE_API void draw_armyFactory(std::array<UnitsStack, Army::STACKS_MAX>&);

#endif // !DRAW_H