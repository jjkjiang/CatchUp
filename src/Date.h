//
// Created by Explo on 4/1/2017.
//

#ifndef CATCHUP_DATE_H
#define CATCHUP_DATE_H

#include <string>
#include <sstream>

class Date {
private:
    std::string date;
public:
    Date() {
        date = "0000/00/00";
    }

    Date(const std::string& date) {
        this->date = date;
    }

    Date(const int& month, const int& day, const int& year) {
        std::stringstream ss;
        ss << year << "/";
        if (month <= 9)
            ss << 0;
        ss << month << "/";
        if (day <= 9)
            ss << 0;
        ss << day;

        date = ss.str();
    }

    // takes advantage of c++ normal string lexigraphical compare to compare dates
    bool operator> (Date rhs) {
        return date > rhs.date;
    }

    bool operator< (Date rhs) {
        return date < rhs.date;
    }

    bool operator== (Date rhs) {
        return date == rhs.date;
    }
};


#endif //CATCHUP_DATE_H
