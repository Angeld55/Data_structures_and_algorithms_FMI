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
struct Task
{
	virtual void run(size_t threadIndex, size_t threadCount) = 0;
	virtual void onBeforeRun(int threadCount) {}
	virtual ~Task() = default;
};

struct ThreadManager
{
	ThreadManager(const ThreadManager&) = delete;
	ThreadManager& operator=(const ThreadManager&) = delete;

	/// Initialize worker count without starting threads
	/// @param threadCount - the number of threads to spawn
	explicit ThreadManager(int threadCount)
		: count(threadCount)
	{}

	/// Start up all threads, must be called before @runThreads is called
	void start()
	{
		running = true;
		currentTask.resize(count, nullptr);

		threads.reserve(count);
		for (int i = 0; i < count; i++)
		{
			threads.emplace_back(&ThreadManager::threadBase, this, i);
		}
		// does not block to wait for threads to start, if they are delayed @runThreads will make sure to wait for them
	}

	/// Schedule the task to be run by the threads and return immediatelly
	/// This function could return before the threads have actually started running the task!
	void runThreadsNoWait(Task& task) {
		{
			std::lock_guard<std::mutex> lock(workMtx);
			for (int c = 0; c < int(currentTask.size()); c++)
			{
				currentTask[c] = &task;
			}

			// inside the lock to ensure this is called before Task::run
			task.onBeforeRun(int(threads.size()));
		}

		workEvent.notify_all();
	}

	/// Start a task on all threads and wait for all of them to finish
	/// @param task - the task to run on all threads
	void runThreads(Task& task) {
		runThreadsNoWait(task);

		// block until task is complete
		if (!unlockedAllTasksDone())
		{
			std::unique_lock<std::mutex> lock(workMtx);
			if (!unlockedAllTasksDone())
			{
				workEvent.wait(lock, [this]()
					{
						return unlockedAllTasksDone();
					});
			}
		}
	}

	/// Blocking wait for all threads to exit, does not interrupt any running Task
	void stop()
	{

		{
			std::lock_guard<std::mutex> lock(workMtx);
			running = false;
		}

		workEvent.notify_all();

		// joining threads will implicitly wait for all of them to finish current task
		for (int c = 0; c < int(threads.size()); c++)
		{
			threads[c].join();
		}

		threads.clear();
		currentTask.clear();
	}

	int getThreadCount() const
	{
		return int(threads.size());
	}

private:

	/// The entry point for all of the threads
	/// @param threadIndex - the 0 based index of the thread
	void threadBase(volatile int threadIndex) {
		while (true) {

			Task* toExecute = nullptr;
			if (running) {
				std::unique_lock<std::mutex> lock(workMtx);

				if (running && currentTask[threadIndex] == nullptr) {
					workEvent.wait(lock, [this, threadIndex]() {
						return currentTask[threadIndex] != nullptr || !running;
						});
				}

				// just copy, and do not clear the value in @currentTask
				// it is used to signal the task is completed
				toExecute = currentTask[threadIndex];
			}

			if (!running) {
				return;
			}

			toExecute->run(threadIndex, int(threads.size()));
			{
				std::lock_guard<std::mutex> lock(workMtx);
				currentTask[threadIndex] = nullptr;
			}

			// Since start and finish share an event this must wake all threads
			// to make sure the caller is awoken and not only some other worker
			workEvent.notify_all();
		}
	}

	/// Check if all elements in @currentTask are nullptr
	/// @return true if at least one task is not nullptr, false otherwise
	bool unlockedAllTasksDone() const {
		for (int c = 0; c < currentTask.size(); c++) {
			if (currentTask[c]) {
				return false;
			}
		}
		return true;
	}

	int count = -1; ///< The number of threads
	std::vector<std::thread> threads; ///< The thread handles

	bool running = false; ///< Flag indicating if threads should quit

	/// The current task for each thread, always must be the same element
	/// Used to track if thread has finished working
	std::vector<Task*> currentTask;
	std::mutex workMtx; ///< Mutex protecting @currentTask and @running

	/// The event used to signal workers when new task is available
	/// Also used by workers to signal when task is finished
	std::condition_variable workEvent;
};


int main()
{
	int count = 10000000;
	std::vector<int> data(count, 1);

	ThreadManager tm(3);
	tm.start();

	//code here?

	std::cout << "result " << 0 << " expected:" << count << std::endl;
	tm.stop();
}
