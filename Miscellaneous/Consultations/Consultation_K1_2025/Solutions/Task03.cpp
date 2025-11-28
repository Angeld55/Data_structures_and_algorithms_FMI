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

// We reuse this function from the previous task
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

unsigned int getOperationPriority(char op)
{
    switch (op)
    {
    case '+':
    case '-':
        return 1;

    case '*':
    case '/':
        return 2;

    case '(':
        return 0;

    default:
        throw std::exception("...");
    }
}

bool isPreceeding(char priorityOp, char op)
{
    return getOperationPriority(priorityOp) >= getOperationPriority(op);
}

// This function can be extended by:
// 1) Processing numbers that are longer than one digit - splitting by separator (for example: whitespace)
// 2) Adding the option to process unary operations - for example: (-7)*6
int evaluateExpression(const std::string& str)
{
    std::stack<char> operations;
    std::string resultReversePolishNotaion;

    for (char ch : str)
    {
        if (ch == '(')
        {
            operations.push(ch);
        }
        else if (ch == ')')
        {
            while (!operations.empty() && operations.top() != '(')
            {
                resultReversePolishNotaion.push_back(operations.top());
                operations.pop();
            }

            if (operations.empty())
            {
                throw std::exception("...");
            }

            operations.pop();
        }
        else if (isdigit(ch))
        {
            resultReversePolishNotaion.push_back(ch);
        }
        else
        {
            while (!operations.empty() && isPreceeding(operations.top(), ch))
            {
                resultReversePolishNotaion.push_back(operations.top());
                operations.pop();
            }

            operations.push(ch);
        }
    }

    while (!operations.empty())
    {
        resultReversePolishNotaion.push_back(operations.top());
        operations.pop();
    }
    
    return evalReversePolish(resultReversePolishNotaion);
}

int main()
{
    std::cout << evaluateExpression("(3-5*4+7)/3");
}
