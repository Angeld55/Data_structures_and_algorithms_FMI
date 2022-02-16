#include "PDA.h"

PDA::PDA(size_t states) : finalStates(states)
{}
void PDA::makeFinal(size_t ind)
{
	if (ind >= finalStates.size())
		return;
	finalStates[ind] = true;
}
void PDA::addTransition(int initialState, char symbol, char stackTopSymbol, int destState, const std::string& stringToReplaceTopStackSymbol)
{
	rules.push_back({ initialState, symbol, stackTopSymbol, destState, stringToReplaceTopStackSymbol });
}
void PDA::applyRuleIfPossible(Computation& current, const Rule& ruleToApply, std::queue<Computation>& q) const
{
	if ((current.state == ruleToApply.initialState) 
		&&((ruleToApply.symbol == '$') || (current.word[0] == ruleToApply.symbol))
		&& (ruleToApply.stackTopSymbol == '$' || current.st.top() == ruleToApply.stackTopSymbol))
	{

		Computation newComputation;

		newComputation.computationSteps = current.computationSteps + 1;
				
		newComputation.state = ruleToApply.destState;
		newComputation.word = ruleToApply.symbol == '$' ? current.word : current.word.substr(1);
		newComputation.st = current.st;

		if (ruleToApply.stackTopSymbol != '$')
			newComputation.st.pop();

		if (ruleToApply.stringToReplaceTopStackSymbol != "$")
		{
			for (int i = ruleToApply.stringToReplaceTopStackSymbol.size() - 1; i >= 0; i--)
				newComputation.st.push(ruleToApply.stringToReplaceTopStackSymbol[i]);
		}
								
		q.push(newComputation);
	}
}

void PDA::printComputation(const Computation& c) const
{
	std::cout << "State: " << c.state << ", Stack: ";
	std::stack<char> stCopy = c.st;
	while (!stCopy.empty())
	{
		std::cout << stCopy.top();
		stCopy.pop();
	}
	std::cout << ", Word: " << c.word << ", STEPS:" << c.computationSteps << std::endl;
}

bool PDA::accepts(const std::string& word) const
{
	Computation currentComputation(0, word, 0);
	
	std::queue<Computation> q;
	currentComputation.st.push('#');
	q.push(currentComputation);

	while (!q.empty())
	{
		Computation current = q.front();
		printComputation(current);

		if (finalStates[current.state] && current.word == "")
		{
			return true;
		}
		if (current.computationSteps == MAX_COMPUTATION_STEPS)
		{
			q.pop();
			continue;
		}
		for (int i = 0; i < rules.size(); i++)
			applyRuleIfPossible(current, rules[i], q);
		q.pop();
	}
	return false;

}
