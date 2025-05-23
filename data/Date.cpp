//
// Created by xyx on 25-5-23.
//
#include "Date.h"

Date::Date(): year(0), month(0), day(0) {}

Date::Date(int y, int m, int d): year(y), month(m), day(d) {}

Date Date::Ztm(const tm &time) {
    return Date(time.tm_year + 1900, time.tm_mon + 1, time.tm_mday);
} //将时间转化为Date

bool Date::operator==(const Date &B) const {
    return (year == B.year && month == B.month && day == B.day);
} //便于后面判断是否已打卡

bool Date::operator<=(const Date &B) const {
    if (year != B.year)return (year <= B.year);
    else if (month != B.month)return (month <= B.month);
    else return (day <= B.day);
}

Date Date::today() {
    time_t now = time(0); //获取从纪元到现在的秒数
    tm *today = localtime(&now); //转化为本地时间
    return Ztm(*today);
} //获取系统当前日期

Date Date::getFirstDayOfWeek() {
    time_t now = time(0); //获取从纪元到现在的秒数
    tm *lo = localtime(&now); //转化为本地时间
    lo->tm_mday -= lo->tm_wday; //回到每周第一天周日
    mktime(lo);
    return Ztm(*lo);
}
