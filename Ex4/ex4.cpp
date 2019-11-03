#include <thread>
#include <future>
#include <iostream>
#include <fstream>

class ThreadLogFile
{
public:
    ThreadLogFile();
    ~ThreadLogFile();
    void print(int value);
private:
    std::mutex write;
    std::ofstream file;
};

ThreadLogFile::ThreadLogFile()
{
    //Create file if its not exists and clear its contents
    this->file.open("log.txt", std::fstream::out | std::ofstream::trunc);
}


ThreadLogFile::~ThreadLogFile()
{
    this->file.close();
}

void ThreadLogFile::print(int value)
{
    //std::lock_guard<std::mutex> guard{this->write};
    this->file << "Log from thread: " << std::this_thread::get_id() << " with value: " << value << std::endl;
}

void logToFile(ThreadLogFile &log, int value)
{
    log.print(value);
    std::thread::id this_id = std::this_thread::get_id();
    std::cout << this_id << std::endl;
}

int main()
{
    std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
    std::cout << "///              BME - C++ II - EXERCISE 3                  ///" << std::endl;
    std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
    std::cout << std::endl;
    std::cout << std::thread::hardware_concurrency() << " concurrent threads are supported.\n";
    {
        std::cout << std::endl;
        std::cout << "***************************************************************" << std::endl;
        std::cout << "***                   Thread basics                         ***" << std::endl;
        std::cout << "***************************************************************" << std::endl;
        ThreadLogFile log;

        auto num_threads = std::thread::hardware_concurrency() * 5;
        std::vector<std::thread> threads;

        for(unsigned int i = 0; i < num_threads; i++)
        {
            threads.push_back(std::thread(logToFile, std::ref(log), i));
        }

        for(auto &t : threads) t.join();

    }

    return 0;
}
