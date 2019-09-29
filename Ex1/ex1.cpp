#include <iostream>
#include <vector>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <cctype>

int main()
{
    std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
    std::cout << "///              BME - C++ II - EXERCISE 1                  ///" << std::endl;
    std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
    std::cout << std::endl;
    std::cout << "***************************************************************" << std::endl;
    std::cout << "***                          STL 1                          ***" << std::endl;
    std::cout << "***************************************************************" << std::endl;

    std::vector<char> alphabet(26);
    std::iota(alphabet.begin(), alphabet.end(), 'a');
    std::copy(alphabet.begin(), alphabet.end(), std::ostream_iterator<char>(std::cout, " "));
    std::cout << std::endl;
    std::reverse_copy(alphabet.begin(), alphabet.end(), std::ostream_iterator<char>(std::cout, " "));

    std::cout << std::endl;
    std::cout << "***************************************************************" << std::endl;
    std::cout << "***                          STL 2                          ***" << std::endl;
    std::cout << "***************************************************************" << std::endl;

    std::ifstream cars_file("cars.txt");
    std::istream_iterator<std::string> start(cars_file), end;
    std::vector<std::string> cars(start, end);
    std::copy(cars.begin(), cars.end(), std::ostream_iterator<std::string>(std::cout, " "));
    std::cout << std::endl << std::endl;
    std::sort(cars.begin(), cars.end());
    std::copy(cars.begin(), cars.end(), std::ostream_iterator<std::string>(std::cout, " "));

    std::cout << std::endl;
    std::cout << "***************************************************************" << std::endl;
    std::cout << "***                          STL 3                          ***" << std::endl;
    std::cout << "***************************************************************" << std::endl;

    for(auto it = cars.cbegin(); it != cars.cend(); ++it)
    {
        if(it->front() == 'A')
        {
            std::cout << *it << " ";
        }
    }
    std::cout << std::endl << std::endl;
    for(const auto& car : cars)
    {
        if(car.front() == 'A')
        {
            std::cout << car << " ";
        }
    }

    std::cout << std::endl;
    std::cout << "***************************************************************" << std::endl;
    std::cout << "***                          STL 4                          ***" << std::endl;
    std::cout << "***************************************************************" << std::endl;

    std::vector<char> filter{'a', 'B', 'c'};

    std::copy_if(cars.begin(), cars.end(), std::ostream_iterator<std::string>(std::cout, " "), [filter](std::string input)
    {
        for(const auto& f : filter)
        {
            if(std::tolower(input.front()) == std::tolower(f))
            {
                return true;
            }
        }
        return false;
    });

    std::cout << std::endl;
    std::cout << "***************************************************************" << std::endl;
    std::cout << "***                    istream_iterators                    ***" << std::endl;
    std::cout << "***************************************************************" << std::endl;
    std::cout << "End the input in Linux with CTRL-D. " << std::endl;
    std::cout << "In Windows press <Enter> CTRL-Z <Enter>." << std::endl;
    std::cout << "Please enter some text: ";
    std::istream_iterator<std::string> input_stream_start(std::cin), input_stream_end;
    std::vector<std::string> words(input_stream_start, input_stream_end);
    std::cout << std::endl;
    std::sort(words.begin(), words.end());
    auto last = std::unique(words.begin(), words.end());
    words.erase(last, words.end());
    std::copy(words.begin(), words.end(), std::ostream_iterator<std::string>(std::cout, " "));

    std::cout << std::endl;
	return 0;
}
