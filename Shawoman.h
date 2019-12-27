#include "BATTLE_API.h"

#ifndef SHAWOMAN_H
#define SHAWOMAN_H

#include "Unit.h"

class BATTLE_API Shawoman : public Unit {
public:
	Shawoman() : Unit("Shawoman", 40, 12, 10, { 7, 12 }, 10.5, { Feature::CAN_USE_ACCELERATION }) {}
};

#endif // !SHAWOMAN_H