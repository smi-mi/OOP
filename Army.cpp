#include "pch.h"

#include <algorithm>
#include "Army.h"

Army::Army(const std::array<UnitsStack, STACKS_MAX>& stacks) {
	m_stacks = stacks;
	for (int i = 0; i < STACKS_MAX; ++i) {
		if (m_stacks[i].get_unit().get_type() == "Undefined") {
			m_stacksNum = i;
			break;
		}
	}
}

bool Army::insert_stack(const UnitsStack& stack) {
	if (m_stacksNum == STACKS_MAX) { return false; }
	m_stacks[m_stacksNum] = stack;
	++m_stacksNum;
	return true;
}
bool Army::erase_stack(const int index) {
	if (index < 0 || index >= STACKS_MAX) { return false; }
	for (int i = index; i < m_stacksNum - 1; ++i) {
		m_stacks[i] = m_stacks[i + 1];
	}
	--m_stacksNum;
	m_stacks[m_stacksNum] = UnitsStack();
	return true;
}
