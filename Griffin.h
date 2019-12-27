#include "BATTLE_API.h"

#ifndef GRIFFIN_H
#define GRIFFIN_H

#include "Unit.h"

class BATTLE_API Griffin : public Unit {
public:
	Griffin() : Unit("Griffin", 30, 7, 5, { 5, 10 }, 15.0, { Feature::ENDLESS_REBUFF }) {}
};

#endif // !GRIFFIN_H