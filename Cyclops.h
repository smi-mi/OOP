#include "BATTLE_API.h"

#ifndef CYCLOPS_H
#define CYCLOPS_H

#include "Unit.h"

class BATTLE_API Cyclops : public Unit {
public:
	Cyclops() : Unit("Cyclops", 85, 20, 15, { 18, 26 }, 10.0, { Feature::SHOOTER }) {}
};

#endif // !CYCLOPS_H