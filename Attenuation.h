#include "BATTLE_API.h"

#ifndef ATTENUATION_H
#define ATTENUATION_H

#include "SpecialAttack.h"

class BATTLE_API Attenuation : public Spell {
public:
	Attenuation() : Spell("attenuation") {}
	virtual void go(BattleUnitsStack& attacker, BattleUnitsStack& target) override {
		target.add_defence(-12);
	}
};

#endif // !ATTENUATION_H