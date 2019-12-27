#include "BATTLE_API.h"

#ifndef ARMY_H
#define ARMY_H

#include <array>
#include "UnitsStack.h"

class BATTLE_API Army {
public:
	static constexpr size_t STACKS_MAX = 6;

	explicit Army(const std::array<UnitsStack, STACKS_MAX>&);

	int get_stacksNum() const { return m_stacksNum; }
	const std::array<UnitsStack, STACKS_MAX>& get_stacks() const { return m_stacks; }

	bool insert_stack(const UnitsStack& stack);
	bool erase_stack(const int);

private:
	int m_stacksNum = STACKS_MAX;
	std::array<UnitsStack, STACKS_MAX> m_stacks;
};

#endif // !ARMY_H