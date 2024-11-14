#include <stack>
#include <string>
#include <iostream>

bool isOpeningBracket(char ch)
{
	return ch == '(' || ch == '[' || ch == '{';
}

bool isMatchingBracket(char ch1, char ch2)
{
	switch (ch1)
	{
	case '(':
		return ch2 == ')';
	case '[':
		return ch2 == ']';
	case '{':
		return ch2 == '}';
	}

	return false;
}

bool isCorrect(const std::string& str)
{
	std::stack<char> brackets;

	for (char ch : str)
	{
		if (isOpeningBracket(ch))
		{
			brackets.push(ch);
		}
		else 
		{
			if (brackets.empty() || !isMatchingBracket(brackets.top(), ch))
			{
				return false;
			}
			else
			{
				brackets.pop();
			}
		}
	}
	return brackets.empty();
}

int main()
{
	std::cout << isCorrect("()");
}