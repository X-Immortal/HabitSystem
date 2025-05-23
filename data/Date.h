//
// Created by xyx on 25-5-23.
//

#ifndef DATE_H
#define DATE_H

#include <ctime>

class Date {
public:
    int year;

    int month;

    int day;

    Date();

    Date(int y, int m, int d);

    static Date Ztm(const tm &time); //将时间转化为Date
    bool operator==(const Date &B) const; //便于后面判断是否已打卡
    bool operator<=(const Date &B) const;

    static Date today(); //获取系统当前日期
    static Date getFirstDayOfWeek();
};

#endif //DATE_H
