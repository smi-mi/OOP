#include "pch.h"

#include <iostream>
#include <string>
#include "Battle.h"
#include "draw.h"

void draw_curStack(const BattleUnitsStack& curStack) {
	std::cout << "\nCurrent stack: ";
	std::cout << curStack.get_armyId() << ":" << curStack.get_unit().get_type() <<
		"(" << curStack.get_unitsAliveNum() << "/" << curStack.get_unitsNum() << ")\n";
}
void draw_queue(const std::deque<BattleUnitsStack*>& queue) {
	std::cout << "\nQueue:\n";
	int size = queue.size();
	for (int i = 0; i < size; ++i) {
		const BattleUnitsStack& stack = *queue[i];
		std::cout << stack.get_armyId() << ":" << stack.get_unit().get_type() <<
			"(" << stack.get_unitsAliveNum() << "/" << stack.get_unitsNum() << ")";
		if (i == size - 1) {
			continue;
		}
		std::cout << " -> ";
	}
	std::cout << "\n";
}
void draw_army(const BattleArmy& army) {
	std::cout << "\n-------------------------------------------------------------------------------------------------------------------------------\n";
	std::cout << "\t\t";
	const int WIDTH = 13;
	for (const auto& stack : army.get_stacks()) {
		std::cout.width(WIDTH);
		std::cout.setf(_IOSleft);
		std::cout << stack.get_unit().get_type();
	}
	std::cout << "\nHP of top unit: ";
	for (const auto& stack : army.get_stacks()) {
		std::cout.width(WIDTH);
		std::cout.setf(_IOSleft);
		std::cout << std::to_string(stack.get_hpTopUnit());
	}
	std::cout << "\nNum of units  : ";
	for (const auto& stack : army.get_stacks()) {
		std::cout.width(WIDTH);
		std::cout.setf(_IOSleft);
		std::cout << std::to_string(stack.get_unitsAliveNum()) + "/" + std::to_string(stack.get_unitsNum());
	}
	std::cout << "\nAttack        : ";
	for (const auto& stack : army.get_stacks()) {
		std::cout.width(WIDTH);
		std::cout.setf(_IOSleft);
		std::cout << stack.get_curAttack();
	}
	std::cout << "\nDefence       : ";
	for (const auto& stack : army.get_stacks()) {
		std::cout.width(WIDTH);
		std::cout.setf(_IOSleft);
		std::cout << stack.get_curDefence();
	}
	std::cout << "\nInitiative    : ";
	for (const auto& stack : army.get_stacks()) {
		std::cout.width(WIDTH);
		std::cout.setf(_IOSleft);
		std::cout << stack.get_curInitiative();
	}
	std::cout << "\n-------------------------------------------------------------------------------------------------------------------------------\n";
}
void draw_armies(const BattleArmy& first, const BattleArmy& second) {
	std::cout << "\n\t\t\t\t\t\t\tFIRST BATTLE ARMY";
	draw_army(first);
	std::cout << "\n\t\t\t\t\t\t\tSECOND BATTLE ARMY";
	draw_army(second);
}

void draw(const Battle& battle) {
	system("cls");
	draw_armies(battle.get_firstArmy(), battle.get_secondArmy());
	draw_queue(battle.get_initiativeScale());
	draw_curStack(battle.get_curStack());

	std::cout << "\nActions: \n";
	std::cout << "1. Attack\n";
	std::cout << "2. Use ability\n";
	std::cout << "3. Wait\n";
	std::cout << "4. Defend\n";
	std::cout << "5. Give up\n";
	std::cout << "> ";
}

void draw_winner(const Battle& battle) {
	std::cout << "\nBattle is completed. Winner: ";
	if (!battle.get_winner()) { std::cout << "noone\n"; } else { std::cout << battle.get_winner()->get_id() << "\n"; }
}

void draw_armyFactory(std::array<UnitsStack, Army::STACKS_MAX>& stacks) {
	const std::vector< std::shared_ptr<Unit> >& unitsCatalog = ArmyFactory::get_unitsCatalog();
	for (int i = 0; i < Army::STACKS_MAX; ++i) {
		system("cls");
		std::cout << "Please choose " << i + 1 << " unit:\n";
		int j = 0;
		for (const std::shared_ptr<Unit>& unit : unitsCatalog) {
			std::cout << j << ". " << unit->get_type() << "\n";
			++j;
		}
		std::cout << "> ";
		int choice, num;
		std::cin >> choice;
		std::cout << "Please enter number of units:\n";
		std::cout << "> ";
		std::cin >> num;
		stacks[i] = UnitsStack(*unitsCatalog[choice], num);
	}
}