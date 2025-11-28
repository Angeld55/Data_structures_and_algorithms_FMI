#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>
#include <queue>
#include <list>

bool isLowercase(char ch)
{
    return ch >= 'a' && ch <= 'z';
}

char toLowercase(char upper)
{
    if (upper >= 'A' && upper <= 'Z')
    {
        return upper - 'A' + 'a';
    }

    return '\0';
}

// The task comes down to validation of parentheses
// Lower case == Opening parenthesis
// Upper case == Closing parenthesis
bool isSymmetric(const std::string& str)
{
    std::stack<char> st;

    for (char ch : str)
    {
        if (isLowercase(ch))
        {
            st.push(ch);
        }
        else
        {
            ch = toLowercase(ch);
            if (!st.empty() && st.top() == ch)
            {
                st.pop();
            }
            else
            {
                return false;
            }
        }
    }

    return st.empty();
}

int main()
{
    std::cout << isSymmetric("qweEWQrtTR");
}
