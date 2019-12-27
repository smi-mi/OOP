#include "BATTLE_API.h"

#ifndef BONE_DRAGON_H
#define BONE_DRAGON_H

#include "Unit.h"

class BATTLE_API BoneDragon : public Unit {
public:
	BoneDragon() : Unit("Bone dragon", 150, 27, 28, { 15, 30 }, 11.0, { Feature::UNDEAD, Feature::CAN_USE_CURSE }) {}
};


#endif // !BONE_DRAGON_H
