//
// Created by xyx on 25-5-23.
//

#include "WeeklyHabit.h"
#include <iostream>

WeeklyHabit::WeeklyHabit() {
}

WeeklyHabit::WeeklyHabit(string name, string description, int target, int frequency):
    Habit(name, description, target), frequency(frequency), finishedWeeks(0), checkinTimes(0),
    firstDayOfThisWeek(Date::today().getFirstDayOfWeek()) {}

void WeeklyHabit::checkWeekTask() {
    if (checkinTimes >= frequency) {
        finishedWeeks++;
        cout << "恭喜你！第" << finishedWeeks << "周任务已完成！" << endl;
        if (finishedWeeks >= target) {
            completed = true;
            cout << "恭喜你！" << name << "习惯已完成！" << endl;
        }
    }
}

void WeeklyHabit::updateCurrentWeek() {
    Date D1 = Date::today().getFirstDayOfWeek();
    if (D1 != firstDayOfThisWeek) {
        if (checkinTimes >= frequency) {
            finishedWeeks++;
            cout << "恭喜你！第" << finishedWeeks << "周任务已完成！" << endl;
            if (finishedWeeks >= target) {
                completed = true;
                cout << "恭喜你！" << name << "习惯已完成！" << endl;
            }
        } else {
            cout << "上周未达标(" << checkinTimes << "/" << frequency << ")！" << endl;
        }
        checkinTimes = 0;
        firstDayOfThisWeek = D1;
    }
} //检查是否为新的一周，若是，则更新
bool WeeklyHabit::checkin() {
    if (completed) {
        cout << "习惯已完成，不能再次打卡！" << endl;
        return false;
    }
    updateCurrentWeek();
    Date today = Date::today();
    if (checkinTimes >= frequency) {
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
        checkinTimes++;
        finishedDates.push_back(today);
        cout << "第" << finishedWeeks + 1 << "周的第" << checkinTimes << "次打卡成功！" << endl;
        checkWeekTask();
        return true;
    } //不满的话检查今天是否已经打卡，已打卡返回false 未打卡+一下天数然后true
}

string WeeklyHabit::toString() const {
    cout << "[每周习惯]" << name << endl;
    if (completed) cout << "(已完成)";
    cout << "习惯描述:" << description << endl;
    cout << "习惯目标：" << target << "周" << endl;
    cout << "已打卡天数：" << finishedDays << "天" << endl;
    cout << "总进度：" << finishedWeeks << "周/" << target << "周" << endl;
    cout << "本周打卡进度：" << checkinTimes << "次/" << frequency << "次" << endl;
    cout << "最近打卡日期：";
    if (finishedDates.empty()) {
        cout << "无" << endl;
    } else {
        const Date &last = finishedDates.back();
        cout << last.year << "-" << last.month << "-" << last.day << endl;
    }
    return "";
}

void WeeklyHabit::saveToFile(ofstream &out) {
    out << "WeeklyHabit" << endl;
    out << name << endl;
    out << description << endl;
    out << target << endl; //目标周数
    out << frequency << endl; //每周目标次数
    out << finishedWeeks << endl; //已完成打卡周数
    out << checkinTimes << endl; //当前周打卡天数
    out << firstDayOfThisWeek.year << " " << firstDayOfThisWeek.month << " " << firstDayOfThisWeek.day << endl;
    //当前周周日
    out << finishedDays << endl; //总的打卡天数
    out << completed << endl; // 新增：保存完成状态
    for (const Date &date: finishedDates) {
        out << date.year << " " << date.month << " " << date.day << endl;
    } //已完成记录
}

void WeeklyHabit::loadFromFile(ifstream &in) {
    getline(in, name);
    getline(in, description);
    in >> target >> frequency >> finishedWeeks >> checkinTimes;
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
