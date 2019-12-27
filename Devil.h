#include "BATTLE_API.h"

#ifndef DEVIL_H
#define DEVIL_H

#include "Unit.h"

class BATTLE_API Devil : public Unit {
public:
	Devil() : Unit("Devil", 166, 27, 25, { 36, 66 }, 11.0, { Feature::CAN_USE_ATTENUATION }) {}
};


#endif // !DEVIL_H