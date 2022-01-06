#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <vector>
#include <thread>
#include <mutex>
#include <stdint.h>
#include <condition_variable>
#include <queue>

using namespace std;


namespace Fibb
{
	std::queue<int> tasks;
	std::mutex workProtect;
	std::condition_variable cv;

	bool isWorking = false;

	size_t fibb(int n)
	{
		if (n == 0 || n == 1)
			return 1;
		return fibb(n - 1) + fibb(n - 2);
	}

	void worker()
	{
		while (true)
		{
			int current = 0;
			{
				if (!isWorking)
					return;

				std::unique_lock<std::mutex> currentLock(workProtect);

				if (tasks.empty())
				{
					cv.wait(currentLock, []() {return !isWorking || !tasks.empty(); });
				}

				if (tasks.empty())
					continue;


				current = tasks.front();
				tasks.pop();
			}
			size_t result = fibb(current);
			std::cout << "fibb(" << current << ")" << result << std::endl;
		}
	}

	void async_fibb()
	{
		isWorking = true;
		std::thread th(worker);

		while (true)
		{
			int input;
			cin >> input;
			if (input >= 0)
			{
				std::lock_guard<std::mutex> guard(workProtect);
				tasks.push(input);
			}
			else
				break;
			cv.notify_one();
		}
		{
			std::lock_guard<std::mutex> guard(workProtect);
			isWorking = false;
		}
		cv.notify_one();
		th.join();
		std::cout << "Done!" << std::endl;
	}
}

int main()
{
	Fibb::async_fibb();
}
