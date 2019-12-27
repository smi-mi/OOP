#include "BATTLE_API.h"

#ifndef FURY_H
#define FURY_H

#include "Unit.h"

class BATTLE_API Fury : public Unit {
public:
	Fury() : Unit("Fury", 16, 5, 3, { 5, 7 }, 16.0, { Feature::IRRESISTIBLE }) {}
};


#endif // !FURY_H