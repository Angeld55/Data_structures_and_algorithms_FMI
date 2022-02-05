
#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <queue>
#include <stack>

bool isOpeningBracket(char ch)
{
	return ch == '(' || ch == '[' || ch == '{';
}
bool isClosingBracket(char ch)
{
	return ch == ')' || ch == ']' || ch == '}';
}
bool isCoresponding(char opening, char closing)
{
	return (opening == '(' && closing == ')') ||
		   (opening == '[' && closing == ']') ||
		   (opening == '{' && closing == '}');
}

char getOpposite(char ch)
{
	if (ch == '(')
		return ')';
	else if (ch == '[')
		return ']';
	else if (ch == '{')
		return '}';
	else if (ch == '}')
		return '{';
	else if (ch == ']')
		return '[';
	else if (ch == ')')
		return '(';
	return ch;
	
}
bool checkBalance(const std::string& str)
{
	std::stack<char> st;
	bool foundMistake = false;

	for (int i = 0; i < str.size(); i++)
	{
		if (isOpeningBracket(str.at(i)))
			st.push(str.at(i));
		else if (isClosingBracket(str.at(i)))
		{
			if (st.empty() || !isCoresponding(st.top(),str.at(i)))
			{
				if(foundMistake)
					return false;
				foundMistake = true;
			}
			else
				st.pop();
		}
	}
	return st.empty() || (st.size() == 1 && !foundMistake);
}

std::string reverseAndFlip(std::string expr)
{
	std::string res(expr.size(), ' ');

	for (int i = expr.size() - 1; i >= 0; i--)
		res.at(i) = getOpposite(expr.at(i));
	return res;
}

bool task(const std::string& str)
{
	return checkBalance(str) || checkBalance(reverseAndFlip(str));
}
int main()
{
	std::cout << task("[sdfsdsd](sdf)(");

}
