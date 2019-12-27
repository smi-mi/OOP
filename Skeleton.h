#include "BATTLE_API.h"

#ifndef SKELETON_H
#define SKELETON_H

#include "Unit.h"

class BATTLE_API Skeleton : public Unit {
public:
	Skeleton() : Unit("Skeleton", 5, 1, 2, { 1, 1 }, 10.0, { Feature::UNDEAD }) {}
};

#endif // !SKELETON_H
