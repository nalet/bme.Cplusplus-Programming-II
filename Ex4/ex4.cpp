#include <thread>
#include <future>
#include <iostream>
#include <fstream>

class ThreadLogFile
{
public:
    ThreadLogFile(std::string filename = "threadLog.txt") : filename(filename)
    {
        //Create file if its not exists and clear its contents
        this->file.open(this->filename, std::fstream::out | std::ofstream::trunc);
    }
    ~ThreadLogFile()
    {
        this->file.close();
    }
    void print(std::thread::id thread_id, int value);
protected:
    std::ofstream file;
    std::string filename{};
};

class ThreadsSaveLogFile : ThreadLogFile
{
public:
    ThreadsSaveLogFile(std::string filename = "threadSaveLog.txt") : ThreadLogFile(filename) {}
    void print(std::thread::id thread_id, int value);
protected:
    std::mutex write;
    std::once_flag header;
};


void ThreadLogFile::print(std::thread::id thread_id, int value)
{
    this->file << "Log from thread: " << thread_id << "\t with value: " << value << std::endl;
}

void ThreadsSaveLogFile::print(std::thread::id thread_id, int value)
{
    std::lock_guard<std::mutex> guard{this->write};
    std::call_once(this->header, [this]()
    {
        this->file << "**************************************HEADER**************************************" << std::endl;
    });
    ThreadLogFile::print(thread_id, value);
}

void logToFile(ThreadLogFile &log, int value)
{
    log.print(std::this_thread::get_id(), value);
}

void logToFileSave(ThreadsSaveLogFile &log, int value)
{
    log.print(std::this_thread::get_id(), value);
}

int main()
{
    std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
    std::cout << "///              BME - C++ II - EXERCISE 4                  ///" << std::endl;
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
        std::cout << "finished Thread basics. Written data to threadLog.txt" << std::endl;

    }

    {
        std::cout << std::endl;
        std::cout << "***************************************************************" << std::endl;
        std::cout << "***                      Data Races                         ***" << std::endl;
        std::cout << "***************************************************************" << std::endl;
        ThreadsSaveLogFile log;

        auto num_threads = std::thread::hardware_concurrency() * 5;
        std::vector<std::thread> threads;

        for(unsigned int i = 0; i < num_threads; i++)
        {
            threads.push_back(std::thread(logToFileSave, std::ref(log), i));
        }

        for(auto &t : threads) t.join();
        std::cout << "finished Data Races. Written data to threadSaveLog.txt" << std::endl;
    }

    return 0;
}
