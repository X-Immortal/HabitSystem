//
// Created by xyx on 25-5-23.
//

#ifndef DATE_H
#define DATE_H

#include <ctime>
#include <string>

using namespace std;

class Date {
    int year;
    int month;
    int day;
    bool modifiable = false;

public:
    Date();

    Date(int y, int m, int d);

    static Date fromTM(const tm &time); //将时间转化为Date
    static tm toTm(const Date &date);
    static tm toTm(int year, int month, int day);
    static Date today(); //获取系统当前日期
    static bool newWeek();

    string toString() const;

    bool operator==(const Date &B) const; //便于后面判断是否已打卡
    bool operator<(const Date &B) const;

    bool canModify() const;
    void setModifiable(bool modifiable);
    int getYear() const;
    int getMonth() const;
    int getDay() const;
    void setDate(int year, int month, int day);

private:
    Date getFirstDayOfWeek() const;
};

#endif //DATE_H
