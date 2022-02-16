#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <string>


class PDA
{
	const int MAX_COMPUTATION_STEPS = 50;
	
	struct Rule
	{
		int initialState;
		char symbol;
		char stackTopSymbol;
		int destState;
		std::string stringToReplaceTopStackSymbol;
	};

	struct Computation
	{
		Computation() : computationSteps(0) {}
		Computation(int state, const std::string& word, int computationSteps) :
			state(state), word(word), computationSteps(computationSteps)
		{}
		int state;
		std::stack<char> st;
		std::string word;
		int computationSteps; 
	};

	std::vector<Rule> rules;
	std::vector<bool> finalStates;
	void printComputation(const Computation& c) const;
	void applyRuleIfPossible(Computation& current, const Rule& ruleToApply, std::queue<Computation>& q) const;

public:
	PDA(size_t states); 
	void makeFinal(size_t ind);
	bool accepts(const std::string& word) const;
	void addTransition(int initialState, char symbol, char stackTopSymbol, int destState, const std::string& stringToReplaceTopStackSymbol);

};