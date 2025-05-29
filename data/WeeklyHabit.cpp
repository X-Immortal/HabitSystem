//
// Created by xyx on 25-5-23.
//

#include "WeeklyHabit.h"
#include <iostream>
#include <sstream>

WeeklyHabit::WeeklyHabit() {
}

WeeklyHabit::WeeklyHabit(string name, string description, int target, int frequency):
    Habit(name, description, target), frequency(frequency), finishedWeeks(0), checkinTimesThisWeek(0),
    firstDayOfThisWeek(Date::today().getFirstDayOfWeek()) {}

void WeeklyHabit::checkWeekTask() {
    if (checkinTimesThisWeek >= frequency) {
        finishedWeeks++;
        cout << "恭喜你！第" << finishedWeeks << "周任务已完成！" << endl;
        if (isCompleted()) {
            cout << "恭喜你！" << name << "习惯已完成！" << endl;
        }
    }
}

void WeeklyHabit::updateCurrentWeek() {
    Date D1 = Date::today().getFirstDayOfWeek();
    if (D1 != firstDayOfThisWeek) {
        if (checkinTimesThisWeek >= frequency) {
            finishedWeeks++;
            cout << "恭喜你！第" << finishedWeeks << "周任务已完成！" << endl;
            if (isCompleted()) {
                cout << "恭喜你！" << name << "习惯已完成！" << endl;
            }
        } else {
            cout << "上周未达标(" << checkinTimesThisWeek << "/" << frequency << ")！" << endl;
        }
        checkinTimesThisWeek = 0;
        firstDayOfThisWeek = D1;
    }
} //检查是否为新的一周，若是，则更新
bool WeeklyHabit::checkin() {
    if (isCompleted()) {
        cout << "习惯已完成，不能再次打卡！" << endl;
        return false;
    }
    updateCurrentWeek();
    Date today = Date::today();
    if (checkinTimesThisWeek >= frequency) {
        cout << "本周打卡已满！" << endl;
        return false;
    } //满的话return false
    else {
        for (const Date &date: finishedDates) {
            if (date == today) {
                cout << "今天已打卡过！" << endl;
                return false;
            }
        }
        finishedDays++;
        checkinTimesThisWeek++;
        finishedDates.push_back(today);
        cout << "第" << finishedWeeks + 1 << "周的第" << checkinTimesThisWeek << "次打卡成功！" << endl;
        checkWeekTask();
        return true;
    } //不满的话检查今天是否已经打卡，已打卡返回false 未打卡+一下天数然后true
}

string WeeklyHabit::toString() const {
    stringstream ss;
    ss << "<html>" << "<p>[每周习惯]";
    if (isCompleted()) {
        ss << "(已完成)";
    }
    ss << "<br/>名称：" << name
        << "<br/>习惯描述：" << description
        << "<br/>目标周数：" << target
        << "<br/>目标频率：" << frequency << "次/周"
        << "<br/>本周已打卡次数：" << checkinTimesThisWeek
        << "<br/>已完成周数：" << finishedWeeks
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

string WeeklyHabit::toSimpleString() const {
    stringstream ss;
    ss << "<html>" << "<p>[每周习惯]";
    if (isCompleted()) {
        ss << "(已完成)";
    }
    ss << "<br/>名称：" << name
        << "<br/>目标周数：" << target
        << "<br/>目标频率：" << frequency << "次/周"
        << "<br/>本周已打卡次数：" << checkinTimesThisWeek
        << "<br/>已完成周数：" << finishedWeeks
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


void WeeklyHabit::saveToFile(ofstream &out) {
    out << "WeeklyHabit" << endl;
    out << name << endl;
    out << description << endl;
    out << target << endl; //目标周数
    out << frequency << endl; //每周目标次数
    out << finishedWeeks << endl; //已完成打卡周数
    out << checkinTimesThisWeek << endl; //当前周打卡天数
    out << firstDayOfThisWeek.year << " " << firstDayOfThisWeek.month << " " << firstDayOfThisWeek.day << endl;
    //当前周周日
    out << finishedDays << endl; //总的打卡天数
    for (const Date &date: finishedDates) {
        out << date.year << " " << date.month << " " << date.day << endl;
    } //已完成记录
}

void WeeklyHabit::loadFromFile(ifstream &in) {
    getline(in, name);
    getline(in, description);
    in >> target >> frequency >> finishedWeeks >> checkinTimesThisWeek;
    in.ignore();
    int y, m, d;
    in >> y >> m >> d;
    firstDayOfThisWeek = Date(y, m, d);
    in.ignore();
    in >> finishedDays;
    in.ignore(); //因为”>>"的输入不会消除换行符，所以得忽略一下换行符
    finishedDates.clear();
    for (int i = 0; i < finishedDays; ++i) {
        int y, m, d;
        in >> y >> m >> d;
        in.ignore();
        finishedDates.push_back(Date(y, m, d));
    }
}
