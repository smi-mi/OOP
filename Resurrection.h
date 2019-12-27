#include "BATTLE_API.h"

#ifndef RESSURACTION_H
#define RESSURACTION_H

#include "SpecialAttack.h"

class BATTLE_API Resurrection : public Spell {
public:
	Resurrection() : Spell("resurection") {}
	virtual void go(BattleUnitsStack& attacker, BattleUnitsStack& target) override {
		int power = attacker.get_unitsAliveNum() * 100;
		target.resurrect_units(power);
	}
};

#endif // !RESSURACTION_H