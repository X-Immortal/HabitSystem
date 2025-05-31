//
// Created by xyx on 25-5-23.
//

#ifndef DATE_H
#define DATE_H

#include <ctime>
#include <string>
#include <QDate>

using namespace std;

class Date : public QDate {
    static bool modifiable;
    static QDate m_today;

public:
    Date(int y, int m, int d);
    explicit Date(const QDate &qdate);

    static Date today(); //获取系统当前日期
    static bool newWeek(const Date &date);

    string toString() const;

    bool operator==(const Date &B) const; //便于后面判断是否已打卡
    bool operator<(const Date &B) const;

    static bool canModify();
    static void setModifiable(bool modifiable);
    int getYear() const;
    int getMonth() const;
    int getDay() const;
    static bool setToday(int year, int month, int day);
    static bool setToday(const QDate &qdate);
    static void setRealToday();

private:
    Date getFirstDayOfWeek() const;
};

#endif //DATE_H
