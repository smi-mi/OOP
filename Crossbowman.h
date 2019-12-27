#include "BATTLE_API.h"

#ifndef CROSSBOWMAN_H
#define CROSSBOWMAN_H

#include "Unit.h"

class BATTLE_API Crossbowman : public Unit {
public:
	Crossbowman() : Unit("Crossbowman", 10, 4, 4, { 2, 8 }, 8.0, { Feature::SHOOTER, Feature::ACCURATE_SHOT }) {}

};

#endif // !CROSSBOWMAN_H