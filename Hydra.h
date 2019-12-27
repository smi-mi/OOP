#include "BATTLE_API.h"

#ifndef HYDRA_H
#define HYDRA_H

#include "Unit.h"

class BATTLE_API Hydra : public Unit {
public:
	Hydra() : Unit("Hydra", 80, 15, 12, { 7, 14 }, 7.0, { Feature::HIT_EVERY, Feature::IRRESISTIBLE }) {}
};


#endif // !HYDRA_H
