#include "BATTLE_API.h"

#ifndef PUNISHING_HIT_H
#define PUNISHING_HIT_H

#include "SpecialAttack.h"

class BATTLE_API PunishingHit : public Spell {
public:
	PunishingHit() : Spell("punishing hit") {}
	virtual void go(BattleUnitsStack& attacker, BattleUnitsStack& target) override {
		target.add_attack(12);
	}
};

#endif // !PUNISHING_HIT_H