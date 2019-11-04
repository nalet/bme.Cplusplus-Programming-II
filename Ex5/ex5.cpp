// Exercise 05 - Producer-Consumer Pattern
#include <iostream>
#include <thread>
#include <sstream>
#include "dataqueue.h" // Your implementation!

using namespace std;
using namespace std::chrono_literals;

static DataQueue<size_t> q{5};
static mutex mu;
static bool finished{false};

void pcout(stringstream& msg)
{
    lock_guard<mutex> coutLock{mu};
    cout << msg.str() << endl;
}

void produce(size_t nbrItems)
{
    for(size_t count{0}; count < nbrItems; ++count)
    {
        std::this_thread::sleep_for(60ms); // Producing time
        q.add(count);
        stringstream ss;
        ss << "Producing --> item " <<   count;
        pcout(ss);
    }

    finished = true;
    stringstream ss;
    ss << " --- Producer done ----";
    pcout(ss);
}

void consume()
{
    while(!q.isEmpty() || !finished)
    {
        std::this_thread::sleep_for(90ms); // Consuming time
        stringstream ss;
        ss << "item " << q.get() << " --> comsumed";
        pcout(ss);
    }
}


int main()
{
    std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
    std::cout << "///              BME - C++ II - EXERCISE 5                  ///" << std::endl;
    std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
    std::cout << std::endl;
    {
        std::cout << std::endl;
        std::cout << "***************************************************************" << std::endl;
        std::cout << "***                Consumer/Producer Pattern                ***" << std::endl;
        std::cout << "***************************************************************" << std::endl;
        // Producer
        thread pThread{produce, 25};

        // Consumer
        thread cThread{consume};

        pThread.join();
        finished = true;
        cThread.join();

        cout << "Finished!" << endl;
    }
    return 0;
}
