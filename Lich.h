#include "BATTLE_API.h"

#ifndef LICH_H
#define LICH_H

#include "Unit.h"

class BATTLE_API Lich : public Unit {
public:
	Lich() : Unit("Lich", 50, 15, 15, { 12, 17 }, 10.0, { Feature::UNDEAD, Feature::CAN_USE_RESURRECTION, Feature::SHOOTER }) {}
};

#endif // !LICH_H