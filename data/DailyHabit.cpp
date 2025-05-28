//
// Created by xyx on 25-5-23.
//

#include "DailyHabit.h"
#include <iostream>
#include <sstream>

DailyHabit::DailyHabit() {}

DailyHabit::DailyHabit(string name, string description, int target): Habit(name, description, target) {}

bool DailyHabit::checkin() {
    if (completed) {
        cout << "习惯已完成，不能再次打卡！" << endl;
        return false;
    }
    Date today = Date::today();
    for (const Date &date: finishedDates) {
        if (date == today) {
            cout << "今天已打卡过" << endl;
            return false;
        }
    }
    finishedDates.push_back(today);
    finishedDays++;
    if (finishedDays >= target) {
        completed = true;
        cout << "恭喜你！" << name << "习惯已完成！" << endl;
    } else {
        cout << "第" << finishedDays << "次打卡成功！" << endl;
    }
    return true;
}

string DailyHabit::toString() const {
    stringstream ss;
    ss << "<html>" << "<p>[每日习惯]";
    if (completed) {
        ss << "(已完成)";
    }
    ss << "<br/>名称：" << name
        << "<br/>习惯描述：" << description
        << "<br/>目标天数：" << target
        << "<br/>已打卡天数：" << finishedDays
        << "<br/>最近打卡日期：";
    if (finishedDates.empty()) {
        ss << "无" << endl;
    } else {
        const Date &last = finishedDates.back();
        ss << last.year << "-" << last.month << "-" << last.day << endl;
    }
    ss << "</p>" << "</html>";
    return ss.str();
}

void DailyHabit::saveToFile(ofstream &out) {
    out << "DailyHabit" << endl;
    out << name << endl;
    out << description << endl;
    out << target << endl;
    out << finishedDays << endl;
    out << completed << endl;
    for (const Date &date: finishedDates) {
        out << date.year << " " << date.month << " " << date.day << endl;
    }
}

void DailyHabit::loadFromFile(ifstream &in) {
    getline(in, name);
    getline(in, description);
    in >> target >> finishedDays;
    in.ignore(); //因为”>>"的输入不会消除换行符，所以得忽略一下换行符
    finishedDates.clear();
    for (int i = 0; i < finishedDays; ++i) {
        int y, m, d;
        in >> y >> m >> d;
        in.ignore();
        finishedDates.push_back(Date(y, m, d));
    }
}
