#include "BATTLE_API.h"

#ifndef SPECIAL_ATTACK_H
#define SPECIAL_ATTACK_H

#include <string>
#include "BattleUnitsStack.h"

class BATTLE_API Spell {
public:
	Spell(const std::string& name) {
		m_name = name;
	}
	virtual void go(BattleUnitsStack& attacker, BattleUnitsStack& target) = 0;
	const std::string& get_name() const { return m_name; }
private:
	std::string m_name;
};

#endif // !SPECIAL_ATTACK_H
