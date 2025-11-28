#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>
#include <queue>
#include <list>

int applyOperation(char op, int first, int second)
{
    switch (op)
    {
    case '+': return first + second;
    case '-': return first - second;
    case '*': return first * second;
    case '/': return first / second;
    default:
        throw std::exception("...");
    }
}

int evalReversePolish(const std::string& str)
{
    std::stack<int> st;
    for (char ch : str)
    {
        if (std::isdigit(ch))
        {
            st.push(ch - '0');
        }
        else
        {
            if (st.size() < 2)
            {
                throw std::exception("...");
            }

            int second = st.top();
            st.pop();
            int first = st.top();
            st.pop();
            
            st.push(applyOperation(ch, first, second));
        }
    }

    if (st.size() != 1)
    {
        throw std::exception("...");
    }

    return st.top();
}

int main()
{
    std::cout << evalReversePolish("345*-7+3/");
}
