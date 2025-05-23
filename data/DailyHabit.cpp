//
// Created by xyx on 25-5-23.
//

#include "DailyHabit.h"
#include <iostream>

DailyHabit::DailyHabit() {}

DailyHabit::DailyHabit(string name1, string d, int T): Habit(name1, d, T) {}

bool DailyHabit::complete() {
    if (completed) {
        cout << "习惯已完成，不能再次打卡！" << endl;
        return false;
    }
    Date today = Date::today();
    for (const Date &date: DoneDates) {
        if (date == today) {
            cout << "今天已打卡过" << endl;
            return false;
        }
    }
    DoneDates.push_back(today);
    totalcurrent++;
    if (totalcurrent >= target) {
        completed = true;
        cout << "恭喜你！" << name << "习惯已完成！" << endl;
    } else {
        cout << "第" << totalcurrent << "次打卡成功！" << endl;
    }
    return true;
}

void DailyHabit::display() {
    cout << "[每日习惯]" << name << endl;
    if (completed) cout << "(已完成)";
    cout << "习惯描述:" << description << endl;
    cout << "习惯目标：" << target << "天" << endl;
    cout << "已打卡天数：" << totalcurrent << "天" << endl;
    cout << "进度：" << totalcurrent << "天/" << target << "天" << endl;
    cout << "最近打卡日期：";
    if (DoneDates.empty()) {
        cout << "无" << endl;
    } else {
        Date &last = DoneDates.back();
        cout << last.year << "-" << last.month << "-" << last.day << endl;
    }
}

void DailyHabit::saveToFile(ofstream &out) {
    out << "DailyHabit" << endl;
    out << name << endl;
    out << description << endl;
    out << target << endl;
    out << totalcurrent << endl;
    out << completed << endl;
    for (const Date &date: DoneDates) {
        out << date.year << " " << date.month << " " << date.day << endl;
    }
}

void DailyHabit::loadFromFile(ifstream &in) {
    getline(in, name);
    getline(in, description);
    in >> target >> totalcurrent;
    in.ignore(); //因为”>>"的输入不会消除换行符，所以得忽略一下换行符
    DoneDates.clear();
    for (int i = 0; i < totalcurrent; ++i) {
        int y, m, d;
        in >> y >> m >> d;
        in.ignore();
        DoneDates.push_back(Date(y, m, d));
    }
}
