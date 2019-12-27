#include "pch.h"

#include <map>
#include "BattleArmy.h"

std::map<int, BattleArmy*> m_armies;
const BattleArmy& find_army_by_id(const int id) { return *(m_armies[id]); }

int BattleArmy::m_curId = 0;
BattleArmy::BattleArmy(const Army& army) : m_id(++m_curId) {
	m_stacksNum = army.get_stacksNum();
	const std::array<UnitsStack, Army::STACKS_MAX>& armyStacks = army.get_stacks();
	for (int i = 0; i < m_stacksNum; ++i) {
		m_stacks[i] = BattleUnitsStack(armyStacks[i], m_id);
	}
	m_armies.insert(std::make_pair(m_id, this));
}

bool BattleArmy::is_dead() const {
	int sumOfLifes = 0;
	for (auto stack : m_stacks) {
		sumOfLifes += stack.get_unitsAliveNum();
	}
	return sumOfLifes == 0;
}

bool BattleArmy::summon_elementals(const BattleUnitsStack& stack) {
	if (m_stacksNum == STACKS_MAX) { return false; }
	m_stacks[m_stacksNum] = stack;
	++m_stacksNum;
	return true;
}