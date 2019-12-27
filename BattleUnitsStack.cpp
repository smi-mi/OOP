#include "pch.h"

#include <algorithm>
#include "BattleUnitsStack.h"
#include "SpecialAttacks.h"

BattleUnitsStack::BattleUnitsStack() : BattleUnitsStack(UnitsStack(), -1) {}
BattleUnitsStack::BattleUnitsStack(const UnitsStack& unitsStack, const int armyId)
	: UnitsStack(unitsStack), m_armyId(armyId)
{
	m_flagConterattack = true;
	m_flagCast = true;
	m_unitsAliveNum = get_unitsNum();
	m_hpTopUnit = get_unit().get_hitPoints();
	m_curAttack = get_unit().get_attack();
	m_curDefence = get_unit().get_defence();
	m_curInitiative = get_unit().get_initiative();

	for (auto& feature : get_unit().get_features()) {
		switch (feature) {
		case Unit::Feature::CAN_USE_ACCELERATION:
			m_spells.push_back(std::shared_ptr<Spell>(new Acceleration()));
			break;
		case Unit::Feature::CAN_USE_ATTENUATION:
			m_spells.push_back(std::shared_ptr<Spell>(new Attenuation()));
			break;
		case Unit::Feature::CAN_USE_CURSE:
			m_spells.push_back(std::shared_ptr<Spell>(new Curse()));
			break;
		case Unit::Feature::CAN_USE_PUNISHING_HIT:
			m_spells.push_back(std::shared_ptr<Spell>(new PunishingHit()));
			break;
		case Unit::Feature::CAN_USE_RESURRECTION:
			m_spells.push_back(std::shared_ptr<Spell>(new Resurrection()));
			break;
		}
	}
	for (auto& feature : get_unit().get_features()) {
		switch (feature) {
		case Unit::Feature::HIT_EVERY:
			m_abilities.push_back(feature);
			break;
		}
	}
}

void BattleUnitsStack::init() {
	m_flagConterattack = true;
	m_curAttack = get_unit().get_attack();
	m_curDefence = get_unit().get_defence();
	m_curInitiative = get_unit().get_initiative();
}

void BattleUnitsStack::take_damage(int power) {
	int unitHitPoints = get_unit().get_hitPoints();
	if (unitHitPoints == 0) { return; }
	if (power < m_hpTopUnit) {
		m_hpTopUnit -= power;
		return;
	}
	power -= m_hpTopUnit;
	--m_unitsAliveNum;

	m_unitsAliveNum -= power / unitHitPoints;
	int powerRemainder = power % unitHitPoints;

	if (powerRemainder != 0) {
		m_hpTopUnit = unitHitPoints - powerRemainder;
	}

	if (m_unitsAliveNum < 0) {
		m_unitsAliveNum = 0;
		m_hpTopUnit = 0;
	}
}
void BattleUnitsStack::resurrect_units(int power) {
	if (get_unit().get_features().find(Unit::Feature::UNDEAD) == get_unit().get_features().end()) {
		return;
	}
	int unitHitPoints = get_unit().get_hitPoints();
	if (m_hpTopUnit + power <= unitHitPoints) {
		m_hpTopUnit += power;
		return;
	}
	power -= unitHitPoints - m_hpTopUnit;

	m_unitsAliveNum += power / unitHitPoints;
	m_hpTopUnit = unitHitPoints;
	int powerLeft = power % unitHitPoints;

	if (powerLeft != 0) {
		++m_unitsAliveNum;
		m_hpTopUnit = powerLeft;
	}

	if (m_unitsAliveNum > get_unitsNum()) {
		m_unitsAliveNum = get_unitsNum();
		m_hpTopUnit = unitHitPoints;
	}
}

void BattleUnitsStack::add_attack(const int delta) {
	m_curAttack += delta;
	if (m_curAttack < 0) { m_curAttack = 0; }
}
void BattleUnitsStack::add_defence(const int delta) {
	m_curDefence += delta;
	if (m_curDefence < 0) { m_curDefence = 0; }
}
void BattleUnitsStack::add_defence(const float coeff) {
	m_curDefence = (int)((float)m_curDefence * coeff);
}
void BattleUnitsStack::add_initiative(const float coeff) {
	m_curInitiative *= coeff;
}

void BattleUnitsStack::set_flagConterattack(const bool flag) {
	if (get_unit().get_features().find(Unit::Feature::ENDLESS_REBUFF) != get_unit().get_features().end()) {
		return;
	}
	m_flagConterattack = flag;
}