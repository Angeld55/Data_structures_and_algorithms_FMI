#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx1, mtx2;
std::condition_variable cv1, cv2;
bool ready1 = false, ready2 = false;

void thread1()
{
    std::unique_lock<std::mutex> lock1(mtx1);
    std::cout << "Thread 1 acquired mtx1 and waiting for ready2\n";
    cv1.wait(lock1, []{ return ready2; }); // Waiting for thread2 to set ready2
    std::cout << "Thread 1 proceeding\n";

    std::unique_lock<std::mutex> lock2(mtx2); // This causes deadlock because thread2 holds mtx2 and is waiting for mtx1
    ready1 = true;
    cv2.notify_one();
}

void thread2()
{
    std::unique_lock<std::mutex> lock2(mtx2);
    std::cout << "Thread 2 acquired mtx2 and waiting for ready1\n";
    cv2.wait(lock2, []{ return ready1; }); // Waiting for thread1 to set ready1
    std::cout << "Thread 2 proceeding\n";

    std::unique_lock<std::mutex> lock1(mtx1); // This causes deadlock because thread1 holds mtx1 and is waiting for mtx2
    ready2 = true;
    cv1.notify_one();
}

int main()
{
    std::thread t1(thread1);
    std::thread t2(thread2);

    t1.join();
    t2.join();

    std::cout << "Finished\n";
    return 0;
}
