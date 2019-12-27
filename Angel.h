#include "BATTLE_API.h"

#ifndef ANGEL_H
#define ANGEL_H

#include "Unit.h"

class BATTLE_API Angel : public Unit {
public:
	Angel() : Unit("Angel", 180, 27, 27, { 45, 45 }, 11.0, { Feature::CAN_USE_PUNISHING_HIT }) {}
};

#endif // !ANGEL_H