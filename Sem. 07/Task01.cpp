#include <iostream>
#include <list>
#include <queue>

using namespace std;

bool isQueueSorted(queue<int>& q, int& lastEl)
{
	if (q.empty())
		return true;

	for (size_t i = 0; i < q.size(); i++)
	{
		int current = q.front();
		q.pop();

		if (i == q.size())
			lastEl = current;

		if ((i != q.size()) && current > q.front())
			return false;

		q.push(current);
	}

	return true;
}
bool isSortedSequence(list<queue<int>>& l)
{
	int lastEl = INT_MIN;
	for (list<queue<int>>::iterator it = l.begin(); it != l.end(); ++it)
	{
		if (it != l.begin())
		{
			if (!(*it).empty() && lastEl > (*it).front())
				return false;
		}

		if (!isQueueSorted(*it, lastEl))
			return false;
	}

	return true;
}

int main()
{
	list<queue<int>> l;

	queue<int> q1;
	q1.push(1);
	q1.push(2);
	q1.push(3);
	queue<int> q2;
	q2.push(6);
	q2.push(9);
	q2.push(10);
	queue<int> q3;
	q3.push(10);
	q3.push(22);
	q3.push(23);
	queue<int> q4;

	l.push_back(q1);
	l.push_back(q2);
	l.push_back(q3);
	l.push_back(q4);

	cout << isSortedSequence(l);
}