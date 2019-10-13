#ifndef BILLIONAIR_H
#define BILLIONAIR_H

#include <string>
#include <iostream>

class Billionair
{
public:
    std::string name{""};
    std::string fortune{""};
    std::string country{""};

    inline friend std::istream& operator >>(std::istream& in, Billionair &b)
    {
        std::getline(in, b.name, '\t');
        std::getline(in, b.fortune, '\t');
        std::getline(in, b.country, '\n');
        return in;
    }

    inline friend std::ostream& operator <<(std::ostream& out, const Billionair &b)
    {
        out << b.name << " " << b.fortune << " " << b.country;
        return out;
    }
};

#endif // BILLIONAIR_H
