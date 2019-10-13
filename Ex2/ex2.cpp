#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iterator>
#include <algorithm>
#include "billionair.h"

int main()
{
    std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
    std::cout << "///              BME - C++ II - EXERCISE 2                  ///" << std::endl;
    std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
    {
        std::cout << std::endl;
        std::cout << "***************************************************************" << std::endl;
        std::cout << "***                            2a                           ***" << std::endl;
        std::cout << "***************************************************************" << std::endl;

        std::vector<std::pair<std::string, std::string>> vec { std::make_pair("Homer", "1111"),
                                                               std::make_pair("Marge", "2222"),
                                                               std::make_pair("Lisa", "3333"),
                                                               std::make_pair("Magy", "4444"),
                                                               std::make_pair("Bart", "5555")};

        std::map<std::string, std::string> map{vec.begin(), vec.end()};

        std::string input;
        while(true)
        {
            std::cout << "Enter name (or Exit ): ";
            std::getline(std::cin, input);
            if(input.compare("Exit") == 0) break;
            auto result = map.find(input);
            std::cout << (result != map.end() ? "Phone number: " +  result->second : "Name not in directory.");
            std::cout << std::endl;
        }
    }

    {
        std::cout << std::endl;
        std::cout << "***************************************************************" << std::endl;
        std::cout << "***                            2b                           ***" << std::endl;
        std::cout << "***************************************************************" << std::endl;

        std::vector<std::pair<std::string, std::string>> vec { std::make_pair("Homer", "1111"), std::make_pair("Homer", "1111"),
                                                               std::make_pair("Marge", "2222"), std::make_pair("Marge", "2222"),
                                                               std::make_pair("Lisa", "3333"), std::make_pair("Lisa", "3333"),
                                                               std::make_pair("Magy", "4444"), std::make_pair("Magy", "4444"),
                                                               std::make_pair("Bart", "5555"), std::make_pair("Bart", "5555")};

        std::multimap<std::string, std::string> map{vec.begin(), vec.end()};

        std::string input;
        while(true)
        {
            std::cout << "Enter name (or Exit ): ";
            std::getline(std::cin, input);
            if(input.compare("Exit") == 0) break;
            auto result = map.equal_range(input);
            if(result.second != map.end())
            {
                std::cout << "Phone numbers: ";
                for(auto pair = result.first; pair != result.second; ++pair)
                {
                    std::cout << pair->second + ", ";
                }
            }
            else
            {
                std::cout << "Name not in directory.";
            }
            std::cout << std::endl;
        }
    }

    {
        std::cout << std::endl;
        std::cout << "***************************************************************" << std::endl;
        std::cout << "***                            3                            ***" << std::endl;
        std::cout << "***************************************************************" << std::endl;

        std::ifstream stream("Forbes2018.txt");
        if(!stream)
        {
            std::cout << " WARNING : File not found !" << std::endl;
            return -1;
        }

        std::vector<Billionair> billionaires;
        std::copy(std::istream_iterator <Billionair>(stream), std::istream_iterator <Billionair>(), std::back_inserter(billionaires));
        //std::copy(billionaires.begin(), billionaires.end(), std::ostream_iterator<Billionair>(std::cout, "\n"));

        std::map<std::string, std::pair<Billionair, int>> map;

        //Sort billionaires on insertion
        for(auto b : billionaires)
        {
            auto _r = map.find(b.country);
            auto pair = map.try_emplace(b.country, std::make_pair(b, 1));
            if(!pair.second)
            {
                pair.first->second.second++;
                if(_r != map.end() && std::stof(pair.first->second.first.fortune) < std::stof(_r->second.first.fortune))
                {
                    map.try_emplace(b.country, std::make_pair(_r->second.first, pair.first->second.second));
                }
            }
        }

        //print all, could us a counter for first 5
        for(auto _m : map)
        {
            std::cout << _m.first << ": " << _m.second.second << " billionaires. Richest is " << _m.second.first.name << " with " << _m.second.first.fortune << "B$" << std::endl;
        }

    }

    return 0;
}
