//
// Created by xyx on 25-5-23.
//
#include "Date.h"

Date::Date(): year(0), month(0), day(0) {
}

Date::Date(int y, int m, int d): year(y), month(m), day(d) {
}

Date Date::fromTM(const tm &time) {
    return Date(time.tm_year + 1900, time.tm_mon + 1, time.tm_mday);
} //将时间转化为Date

tm Date::toTm(const Date &date) {
    return toTm(date.year, date.month, date.day);
}

tm Date::toTm(int year, int month, int day) {
    tm atime = {};
    atime.tm_year = year - 1900;
    atime.tm_mon = month - 1;
    atime.tm_mday = day;
    mktime(&atime);
    return atime;
}

bool Date::operator==(const Date &B) const {
    return year == B.year && month == B.month && day == B.day;
} //便于后面判断是否已打卡

bool Date::operator<(const Date &B) const {
    return this->year < B.year || (year == B.year && month < B.month) || (year == B.year && month == B.month && day < B.day);
}

Date Date::today() {
    time_t now = time(0); //获取从纪元到现在的秒数
    tm *today = localtime(&now); //转化为本地时间
    return fromTM(*today);
} //获取系统当前日期

Date Date::getFirstDayOfWeek() const {
    tm atime = toTm(year, month, day);
    atime.tm_mday -= atime.tm_wday;
    mktime(&atime);
    return fromTM(atime);
}

string Date::toString() const {
    return to_string(year) + "年" + to_string(month) + "月" + to_string(day) + "日";
}

bool Date::newWeek() {
    Date today = Date::today();
    return today == today.getFirstDayOfWeek();
}

int Date::getYear() const {
    return year;
}

int Date::getMonth() const {
    return month;
}

int Date::getDay() const {
    return day;
}

bool Date::canModify() const {
    return modifiable;
}

void Date::setDate(int year, int month, int day) {
    if (!canModify()) {
        return;
    }
    Date date = fromTM(toTm(year, month, day));
    this->year = date.year;
    this->month = date.month;
    this->day = date.day;
}

void Date::setModifiable(bool modifiable) {
    this->modifiable = modifiable;
}




