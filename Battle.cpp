#include "pch.h"

#include <algorithm>
#include <random>
#include "draw.h"
#include "Battle.h"
#include "SpecialAttack.h"

std::vector< std::shared_ptr<Unit> > ArmyFactory::m_unitsCatalog = {
	std::shared_ptr<Unit>(new Unit()),
	std::shared_ptr<Unit>(new Angel()),
	std::shared_ptr<Unit>(new BoneDragon()),
	std::shared_ptr<Unit>(new Crossbowman()),
	std::shared_ptr<Unit>(new Cyclops()),
	std::shared_ptr<Unit>(new Devil()),
	std::shared_ptr<Unit>(new Fury()),
	std::shared_ptr<Unit>(new Griffin()),
	std::shared_ptr<Unit>(new Hydra()),
	std::shared_ptr<Unit>(new Lich()),
	std::shared_ptr<Unit>(new Shawoman()),
	std::shared_ptr<Unit>(new Skeleton())
};

void Battle::run() {
	m_isGoing = true;
	m_cutState = State::STARTING_ROUND;

	while (is_going()) {
		init_armies();
		init_initiativeScale();
		++m_roundsNum;
		run_round();
	}

	draw_winner(*this);
}
/*DOING
void Battle::update() {
	switch (m_cutState) {
	case State::STARTING_ROUND:
		init_armies();
		init_initiativeScale();
		++m_roundsNum;
		m_cutState = State::SHOWING_ACTIONS;
		break;
	case State::SHOWING_ACTIONS:
		m_curStack = m_initiativeScale.front();
		m_initiativeScale.pop_front();
		--m_waitingIndex;
		if (m_waitingIndex < 0) { m_waitingIndex = 0; }
		break;
	case State::STOP:
		m_isGoing = false;
		break;
	}
}
*/


void Battle::init_armies() {
	for (auto& stack : m_firstArmy.get_stacks()) {
		stack.init();
	}
	for (auto& stack : m_secondArmy.get_stacks()) {
		stack.init();
	}
}
void Battle::init_initiativeScale() {
	for (auto& stack : m_firstArmy.get_stacks()) {
		const std::string& type = stack.get_unit().get_type();
		BattleUnitsStack* stack_ptr = &stack;
		if (type != "Undefined") m_initiativeScale.push_back(stack_ptr);
	}
	for (auto& stack : m_secondArmy.get_stacks()) {
		const std::string& type = stack.get_unit().get_type();
		BattleUnitsStack* stack_ptr = &stack;
		if (type != "Undefined") m_initiativeScale.push_back(stack_ptr);
	}
	std::sort(m_initiativeScale.begin(), m_initiativeScale.end(),
		[](const BattleUnitsStack* a, const BattleUnitsStack* b) {
			return a->get_curInitiative() > b->get_curInitiative();
		});
	m_waitingIndex = m_initiativeScale.size();
}

void Battle::run_round() {
	while (!m_initiativeScale.empty() && is_going()) {
		m_curStack = m_initiativeScale.front();
		draw(*this);

		m_initiativeScale.pop_front();
		--m_waitingIndex;
		if (m_waitingIndex < 0) { m_waitingIndex = 0; }

		int action;
		std::cin >> action;
		switch (static_cast<Action>(action)) {
		case Action::ATTACK:
			attack(*m_curStack);
			break;
		case Action::USE_POWER:
			use_power(*m_curStack);
			break;
		case Action::WAIT:
			wait(*m_curStack);
			break;
		case Action::DEFEND:
			defend(*m_curStack);
			break;
		case Action::GIVE_UP:
			give_up(*m_curStack);
			break;
		}

		std::sort(m_initiativeScale.begin(), m_initiativeScale.begin() + m_waitingIndex,
			[](const BattleUnitsStack* a, const BattleUnitsStack* b) {
				return a->get_curInitiative() > b->get_curInitiative();
			});
		std::sort(m_initiativeScale.begin() + m_waitingIndex, m_initiativeScale.end(),
			[](const BattleUnitsStack* a, const BattleUnitsStack* b) {
				return a->get_curInitiative() < b->get_curInitiative();
			});

		if (m_firstArmy.is_dead() && m_secondArmy.is_dead()) {
			m_isGoing = false;
		} else if (m_firstArmy.is_dead()) {
			m_winner = &m_secondArmy;
			m_isGoing = false;
		} else if (m_secondArmy.is_dead()) {
			m_winner = &m_firstArmy;
			m_isGoing = false;
		}
	}
}
void Battle::attack(BattleUnitsStack& stack) {
	std::cout << "Who's attack target?\n";
	std::cout << "> ";
	int index;
	std::cin >> index;
	BattleUnitsStack* target_ptr = nullptr;
	if (index >= 0 && index <= 8) {
		target_ptr = &m_firstArmy.get_stacks()[index];
	} else if (index >= 9 && index <= 17) {
		target_ptr = &m_secondArmy.get_stacks()[index - 9];
	}
	if (!target_ptr) { return; }

	BattleUnitsStack& target = *target_ptr;
	attack_one_another(stack, target);

	if (target.can_Conterattack() &&
		target.get_unit().get_features().find(Unit::Feature::SHOOTER) == target.get_unit().get_features().end() &&
		stack.get_unit().get_features().find(Unit::Feature::IRRESISTIBLE) == stack.get_unit().get_features().end() &&
		stack.get_unit().get_features().find(Unit::Feature::SHOOTER) == stack.get_unit().get_features().end())
	{
		attack_one_another(target, stack);
		target.set_flagConterattack(false);
	}
}
void Battle::attack_one_another(BattleUnitsStack& attacker, BattleUnitsStack& target) {
	int minDamage, maxDamage;
	const int attack = attacker.get_curAttack();
	const std::set<Unit::Feature>& attackerFeatures = attacker.get_unit().get_features();
	const int defence = attackerFeatures.find(Unit::Feature::ACCURATE_SHOT) == attackerFeatures.end() ?
		target.get_curDefence() : 0;


	const int unitsNum = attacker.get_unitsAliveNum();
	const int min = attacker.get_unit().get_damageRange().first;
	const int max = attacker.get_unit().get_damageRange().second;

	if (attack > defence) {
		minDamage = unitsNum * min * (1 + (attack - defence) / 20);
		maxDamage = unitsNum * max * (1 + (attack - defence) / 20);
	} else {
		minDamage = unitsNum * min / (1 + (defence - attack) / 20);
		maxDamage = unitsNum * max / (1 + (defence - attack) / 20);
	}
	std::random_device generator;
	int damage = generator() % (maxDamage - minDamage + 1) + minDamage;
	target.take_damage(damage);
}
void Battle::attack_army(BattleUnitsStack& stack, BattleArmy& targetArmy) {
	for (auto& target : targetArmy.get_stacks()) {
		attack_one_another(stack, target);
	}
	for (auto& target : targetArmy.get_stacks()) {
		if (target.can_Conterattack() &&
			target.get_unit().get_features().find(Unit::Feature::SHOOTER) == target.get_unit().get_features().end() &&
			stack.get_unit().get_features().find(Unit::Feature::IRRESISTIBLE) == stack.get_unit().get_features().end() &&
			stack.get_unit().get_features().find(Unit::Feature::SHOOTER) == stack.get_unit().get_features().end())
		{
			attack_one_another(target, stack);
			target.set_flagConterattack(false);
		}
	}
}
void Battle::use_power(BattleUnitsStack& stack) {
	std::cout << "Stack features:\n";
	int abilitiesNum = stack.get_abilities().size();
	int num = 1;
	for (auto& feature : stack.get_abilities()) {
		std::cout << num << ". ";
		switch (feature) {
		case Unit::Feature::HIT_EVERY:
			std::cout << "Hit everyone";
			break;
		}
		std::cout << "\n";
		++num;
	}
	for (std::shared_ptr<Spell> spell : stack.get_spells()) {
		std::cout << num << ". Spell: " << spell->get_name() << "\n";
		++num;
	}
	std::cout << "> ";

	int featureIndex;
	std::cin >> featureIndex;
	if (abilitiesNum == 1) {
		if (featureIndex == 1) {
			if (stack.get_armyId() == m_firstArmy.get_id()) {
				attack_army(stack, m_secondArmy);
			} else {
				attack_army(stack, m_firstArmy);
			}
			return;
		}
		--featureIndex;
	}

	if (featureIndex <= 0 || featureIndex > abilitiesNum + stack.get_spells().size()) { return; }

	std::shared_ptr<Spell> spell = stack.get_spells()[featureIndex - 1];
	std::cout << "Who's spell target?\n";
	std::cout << "> ";
	int index;
	std::cin >> index;
	BattleUnitsStack* target_ptr = nullptr;
	if (index >= 0 && index <= 8) {
		target_ptr = &m_firstArmy.get_stacks()[index];
	} else if (index >= 9 && index <= 17) {
		target_ptr = &m_secondArmy.get_stacks()[index - 9];
	}
	if (!target_ptr) { return; }
	BattleUnitsStack& target = *target_ptr;
	spell->go(stack, target);
}
void Battle::wait(BattleUnitsStack& stack) {
	m_initiativeScale.insert(m_initiativeScale.begin() + m_waitingIndex, &stack);
}
void Battle::defend(BattleUnitsStack& stack) {
	stack.add_defence(1.3f);
}
void Battle::give_up(const BattleUnitsStack& stack) {
	if (stack.get_armyId() == m_firstArmy.get_id()) {
		m_winner = &m_secondArmy;
	} else if (stack.get_armyId() == m_secondArmy.get_id()) {
		m_winner = &m_firstArmy;
	}
	m_isGoing = false;
}