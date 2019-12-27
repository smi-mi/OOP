#include "BATTLE_API.h"

#ifndef ACCELERATION_H
#define ACCELERATION_H

#include "SpecialAttack.h"

class BATTLE_API Acceleration : public Spell {
public:
	Acceleration() : Spell("acceleration") {}
	virtual void go(BattleUnitsStack& attacker, BattleUnitsStack& target) override {
		target.add_initiative(1.4f);
	}
};

#endif // !ACCELERATION_H