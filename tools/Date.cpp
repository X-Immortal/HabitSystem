//
// Created by xyx on 25-5-23.
//
#include "Date.h"

bool Date::modifiable = false;

QDate Date::m_today = currentDate();

Date::Date(int y, int m, int d) : QDate(y, m, d) {
}

Date::Date(const QDate &qdate) : QDate(qdate) {
}

bool Date::operator==(const Date &B) const {
    return year() == B.year() && month() == B.month() && day() == B.day();
} //便于后面判断是否已打卡

bool Date::operator<(const Date &B) const {
    return this->year() < B.year() || (year() == B.year() && month() < B.month()) || (year() == B.year() && month() == B.month() && day() < B.day());
}

Date Date::today() {
    return Date(m_today);
} //获取系统当前日期

Date Date::getFirstDayOfWeek() const {
    return Date(addDays(1 - dayOfWeek()));
}

string Date::toString() const {
    return QDate::toString("yyyy年MM月dd日").toStdString();
}

bool Date::newWeek(const Date &date) {
    return date.getFirstDayOfWeek() != today().getFirstDayOfWeek();
}

int Date::getYear() const {
    return year();
}

int Date::getMonth() const {
    return month();
}

int Date::getDay() const {
    return day();
}

bool Date::canModify() {
    return modifiable;
}

bool Date::setToday(int year, int month, int day) {
    if (!canModify()) {
        return false;
    }
    m_today.setDate(year, month, day);
    return true;
}

bool Date::setToday(const QDate &qdate) {
    return setToday(qdate.year(), qdate.month(), qdate.day());
}


void Date::setModifiable(bool modifiable) {
    Date::modifiable = modifiable;
}

void Date::setRealToday() {
    m_today = currentDate();
}




