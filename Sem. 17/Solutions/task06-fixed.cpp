#include<iostream>
#include<string>
#include<stack>

bool isOpeningBracket(char ch) {
	return ch == '(' || ch == '[' || ch == '{';
}

bool isClosingBracket(char ch) {
	return ch == ')' || ch == ']' || ch == '}';
}

bool isCoresponding(char opening, char closing) {
	return (opening == '(' && closing == ')') ||
		(opening == '[' && closing == ']') ||
		(opening == '{' && closing == '}');
}

std::string removeSymbolAtIndex(const std::string& expr, int index) {
	if (index < 0 || index >= expr.size())
		throw std::exception("Invalid index");

	return std::string(expr.begin(), expr.begin() + index) + std::string(expr.begin() + index + 1, expr.end());
}

bool solution(const std::string& expr, bool seenMistake = false) {
	std::stack<char> s;

	for (int i = 0; i < expr.size(); i++) {
		if (isOpeningBracket(expr.at(i)))
			s.push(expr.at(i));
		else if (isClosingBracket(expr.at(i))) {
			if (s.empty() || !isCoresponding(s.top(), expr.at(i))) {
				if (seenMistake)
					return false;
				else {
					bool result = solution(removeSymbolAtIndex(expr, i), true);
					if (i > 0)
						result = result || solution(removeSymbolAtIndex(expr, i - 1), true);
					return result;
				}
			}
			s.pop();
		}
	}
	return s.empty() || (s.size() == 1 && !seenMistake);
}

int main() {
  // fix ((([))) corner case
}
