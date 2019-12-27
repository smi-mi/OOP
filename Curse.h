#include "BATTLE_API.h"

#ifndef CURSE_H
#define CURSE_H

#include "SpecialAttack.h"

class BATTLE_API Curse : public Spell {
public:
	Curse() : Spell("curse") {}
	virtual void go(BattleUnitsStack& attacker, BattleUnitsStack& target) override {
		target.add_attack(-12);
	}
};

#endif // !CURSE_H