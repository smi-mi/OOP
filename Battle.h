#include "BATTLE_API.h"

#ifndef BATTLE_H
#define BATTLE_H

#include <deque>
#include <memory>
#include "BattleUnitsStack.h"
#include "BattleArmy.h"
#include "ArmyFactory.h"
#include "draw.h"

class BATTLE_API Battle {
public:
	enum class State {
		STARTING_ROUND,
		SHOWING_ACTIONS,
		STOP
	};
	enum class Action {
		ATTACK = 1,
		USE_POWER = 2,
		WAIT = 3,
		DEFEND = 4,
		GIVE_UP = 5
	};
	Battle(BattleArmy& first, BattleArmy& second)
		: m_firstArmy(first), m_secondArmy(second)
	{}

	void run();
	//void update();

	bool  is_going() const { return m_isGoing; }
	const BattleArmy* get_winner() const { return m_winner; }
	const BattleUnitsStack& get_curStack() const { return *m_curStack; }
	const std::deque<BattleUnitsStack*>& get_initiativeScale() const { return m_initiativeScale; }
	const BattleArmy& get_firstArmy()  const { return m_firstArmy; }
	const BattleArmy& get_secondArmy() const { return m_secondArmy; }

private:
	bool m_isGoing = false;
	State m_cutState = State::STOP;
	int m_roundsNum = 0;
	BattleArmy* m_winner = nullptr;
	BattleArmy& m_firstArmy;
	BattleArmy& m_secondArmy;

	std::deque<BattleUnitsStack*> m_initiativeScale = {};
	BattleUnitsStack* m_curStack = nullptr;
	int m_waitingIndex = -1;
	void init_initiativeScale();
	void init_armies();

	void run_round();
	void attack(BattleUnitsStack&);
	void attack_one_another(BattleUnitsStack& attacker, BattleUnitsStack& target);
	void attack_army(BattleUnitsStack& attacker, BattleArmy& target);
	void use_power(BattleUnitsStack&);
	void wait(BattleUnitsStack&);
	void defend(BattleUnitsStack&);
	void give_up(const BattleUnitsStack&);
};

#endif // !BATTLE_H
