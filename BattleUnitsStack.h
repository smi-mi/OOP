#include "BATTLE_API.h"

#ifndef BATTLE_UNITS_STACK_H
#define BATTLE_UNITS_STACK_H

#include <vector>
#include <memory>
#include "UnitsStack.h"

class Spell;

class BATTLE_API BattleUnitsStack : public UnitsStack {
public:
	BattleUnitsStack();
	explicit BattleUnitsStack(const UnitsStack&, const int);

	void init();

	int   get_armyId()        const { return m_armyId; }
	int   get_unitsAliveNum() const { return m_unitsAliveNum; }
	int   get_hpTopUnit()     const { return m_hpTopUnit; }
	int   get_curAttack()     const { return m_curAttack; }
	int   get_curDefence()    const { return m_curDefence; }
	float get_curInitiative() const { return m_curInitiative; }

	void take_damage(int power);
	void resurrect_units(int power);

	void add_attack(const int);
	void add_defence(const int);
	void add_defence(const float);
	void add_initiative(const float);

	bool can_Conterattack() const { return m_flagConterattack; }
	void set_flagConterattack(const bool flag);
	bool can_Cast() const { return m_flagCast; }
	void set_flagCast(const bool flag) { m_flagCast = flag; }

	std::vector< std::shared_ptr<Spell> >& get_spells() { return m_spells; }
	std::vector<Unit::Feature>& get_abilities() { return m_abilities; }

private:
	std::vector< std::shared_ptr<Spell> > m_spells;
	std::vector<Unit::Feature> m_abilities;

	bool m_flagConterattack;
	bool m_flagCast;
	int m_armyId;

	int m_unitsAliveNum;
	int m_hpTopUnit;
	int m_curAttack;
	int m_curDefence;
	float m_curInitiative;
};

#endif // !BATTLE_UNITS_STACK_H