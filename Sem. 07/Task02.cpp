#include <iostream>
#include <list>
#include <queue>

using namespace std;

bool areQueuesOfSameSize(const queue<int>& lhs, const queue<int>& rhs)
{
	return lhs.size() == rhs.size();
}
void mergeQueues(queue<int>& lhs, queue<int>& rhs)
{
	while (!rhs.empty())
	{
		lhs.push(rhs.front());
		rhs.pop();
	}
}
void equalize(queue<int>& lhs, queue<int>& rhs)
{
	bool isLhsBigger = lhs.size() > rhs.size() ? true : false;

	if (isLhsBigger)
	{
		while (lhs.size() > rhs.size() + 1)
		{
			rhs.push(lhs.front());
			lhs.pop();
		}
	}
	else
	{
		while (rhs.size() > lhs.size() + 1)
		{
			lhs.push(rhs.front());
			rhs.pop();
		}
	}
}

void modifyList(list<queue<int>>& l)
{
	if (l.empty())
		return;

	list<queue<int>>::iterator it = l.begin();

	while (it != l.end())
	{
		list<queue<int>>::iterator next = it;
		++next;

		if (next == l.end())
			break;

		if (areQueuesOfSameSize(*it, *next))
		{
			mergeQueues(*it, *next);
			l.erase(next);
			continue;
		}
		else
		{
			++it;

			if (++next == l.end())
				break;

			if (!areQueuesOfSameSize(*it, *next))
			{
				equalize(*it, *next);
				++it;
			}
		}
	}
}

int main()
{
	list<queue<int>> l;

	queue<int> q1;
	q1.push(2);
	q1.push(4);
	q1.push(6);
	queue<int> q2;
	q2.push(8);
	q2.push(0);
	q2.push(7);
	queue<int> q3;
	q3.push(5);
	q3.push(7);
	q3.push(9);
	q3.push(23);
	q3.push(22);
	queue<int> q4;
	q4.push(9);
	q4.push(1);
	queue<int> q5;
	q5.push(2);
	queue<int> q6;
	q6.push(1);
	queue<int> q7;
	q7.push(33);
	q7.push(44);

	l.push_back(q1);
	l.push_back(q2);
	l.push_back(q3);
	l.push_back(q4);
	l.push_back(q5);
	l.push_back(q6);
	l.push_back(q7);

	modifyList(l);
}