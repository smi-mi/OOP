#include "BATTLE_API.h"

#ifndef UNIT_H
#define UNIT_H

#include <set>
#include <string>
#include <iostream>

class BATTLE_API Unit {
public:
	enum class Feature {
		SHOOTER,
		ACCURATE_SHOT,
		UNDEAD,
		IRRESISTIBLE,
		HIT_EVERY,
		ENDLESS_REBUFF,
		CAN_USE_ACCELERATION,
		CAN_USE_ATTENUATION,
		CAN_USE_CURSE,
		CAN_USE_PUNISHING_HIT,
		CAN_USE_RESURRECTION
	};

	Unit() : Unit("Undefined", 0, 0, 0, { 0, 0 }, 0.0, {}) {}
	Unit(const std::string& type, const int hitPoints, const int attack,
		const int defence, const std::pair<int, int> damageRange,
		const float initiative, const std::set<Feature>& features)
	{
		m_type = type;
		m_hitPoints = hitPoints;
		m_attack = attack;
		m_defence = defence;
		m_damageRange = damageRange;
		m_initiative = initiative;
		m_features = features;
	}

	const std::set<Feature>& get_features() const { return m_features; }

	const std::string& get_type() const { return m_type; }
	int   get_hitPoints()  const { return m_hitPoints; }
	int   get_attack()     const { return m_attack; }
	int   get_defence()    const { return m_defence; }
	std::pair<int, int> get_damageRange() const { return m_damageRange; }
	float get_initiative() const { return m_initiative; }

private:
	std::set<Feature> m_features;

	std::string m_type;
	int   m_hitPoints;
	int   m_attack;
	int   m_defence;
	std::pair<int, int> m_damageRange;
	float m_initiative;
};

#endif // !UNIT_H