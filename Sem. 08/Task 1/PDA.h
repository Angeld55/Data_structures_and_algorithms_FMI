#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <string>
using namespace std;


class PDA
{
	const int MAX_COMPUTATION_STEPS = 50;
	
	struct Rule
	{
		int initialState;
		char symbol;
		char stackTopSymbol;
		int destState;
		string stringToReplaceTopStackSymbol;
	};

	struct Computation
	{
		Computation() :computationSteps(0) {}
		Computation(int state, string word, int computationSteps) :
			state(state), word(word), computationSteps(computationSteps)
		{}
		int state;
		stack<char> st;
		string word;
		int computationSteps; 
	};

	vector<Rule> rules;
	vector<bool> finalStates;
	void printComputation(const Computation& c);
	void ApplyRuleIfPossible(Computation& current, Rule& r, queue<Computation>& q);

public:
	PDA(size_t states); 
	void makeFinal(size_t ind);
	bool accepts(std::string word);
	void addTransition(int initialState, char symbol, char stackTopSymbol, int destState, string stringToReplaceTopStackSymbol);

};