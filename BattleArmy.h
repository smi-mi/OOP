#include "BATTLE_API.h"

#ifndef BATTLE_ARMY_H
#define BATTLE_ARMY_H

#include <array>
#include <memory>
#include "BattleUnitsStack.h"
#include "Army.h"

class BATTLE_API BattleArmy {
public:
	static constexpr size_t STACKS_MAX = 9;

	explicit BattleArmy(const Army&);

	std::array<BattleUnitsStack, STACKS_MAX>& get_stacks() { return m_stacks; }
	const std::array<BattleUnitsStack, STACKS_MAX>& get_stacks() const { return m_stacks; }
	const int get_id() const { return m_id; }
	bool is_dead() const;

	bool summon_elementals(const BattleUnitsStack&);

private:
	static int m_curId;
	const int m_id;

	int m_stacksNum;
	std::array<BattleUnitsStack, STACKS_MAX> m_stacks;
};

const BattleArmy& find_army_by_id(const int);

#endif // !BATTLE_ARMY_H;