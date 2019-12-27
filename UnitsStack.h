#include "BATTLE_API.h"

#ifndef UNITS_STACK_H
#define UNITS_STACK_H

#include <string>
#include <memory>
#include "Units.h"

class BATTLE_API UnitsStack {
public:
	UnitsStack() : UnitsStack(Unit(), 0) {}
	UnitsStack(const Unit& unit, const int unitsNum) {
		m_unit = std::make_shared<Unit>(unit);
		m_unitsNum = unitsNum >= 0 ? unitsNum : 0;
	}

	const Unit& get_unit() const { return *m_unit; }
	int get_unitsNum()     const { return m_unitsNum; }

private:
	std::shared_ptr<Unit> m_unit;
	int m_unitsNum;
};

#endif // !UNITS_STACK_H