#ifndef ARMY_FACTORY_H
#define ARMY_FACTORY_H

#include "BATTLE_API.h"

#include <vector>
#include <memory>
#include "Army.h"
#include "Unit.h"
#include "UnitsStack.h"

class BATTLE_API ArmyFactory {
public:
	ArmyFactory() = delete;

	static void add_unit(const Unit& unit) {
		m_unitsCatalog.push_back(std::make_shared<Unit>(unit));
	}
	static const std::vector< std::shared_ptr<Unit> >& get_unitsCatalog() { return m_unitsCatalog; }
	static Army make_army(const std::array<UnitsStack, Army::STACKS_MAX>& unitsStack) {
		Army newArmy = Army(unitsStack);
		return newArmy;
	}

private:
	static std::vector< std::shared_ptr<Unit> > m_unitsCatalog;
};

#endif // !ARMY_FACTORY_H