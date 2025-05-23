//
// Created by xyx on 25-5-23.
//

#include "WeeklyHabit.h"
#include <iostream>

WeeklyHabit::WeeklyHabit() {
}

WeeklyHabit::WeeklyHabit(string name1, string d, int WT, int fre):
    Habit(name1, d, WT), frequency(fre), currentdoneweek(0), wcurrent(0),
    currentweekfirstday(Date::today().getFirstDayOfWeek()) {}

void WeeklyHabit::checkWeekTask() {
    if (wcurrent >= frequency) {
        currentdoneweek++;
        cout << "恭喜你！第" << currentdoneweek << "周任务已完成！" << endl;
        if (currentdoneweek >= target) {
            completed = true;
            cout << "恭喜你！" << name << "习惯已完成！" << endl;
        }
    }
}

void WeeklyHabit::updateCurweek() {
    Date D1 = Date::today().getFirstDayOfWeek();
    if (D1 != currentweekfirstday) {
        if (wcurrent >= frequency) {
            currentdoneweek++;
            cout << "恭喜你！第" << currentdoneweek << "周任务已完成！" << endl;
            if (currentdoneweek >= target) {
                completed = true;
                cout << "恭喜你！" << name << "习惯已完成！" << endl;
            }
        } else {
            cout << "上周未达标(" << wcurrent << "/" << frequency << ")！" << endl;
        }
        wcurrent = 0;
        currentweekfirstday = D1;
    }
} //检查是否为新的一周，若是，则更新
bool WeeklyHabit::complete() {
    if (completed) {
        cout << "习惯已完成，不能再次打卡！" << endl;
        return false;
    }
    updateCurweek();
    Date today = Date::today();
    if (wcurrent >= frequency) {
        cout << "本周打卡已满！" << endl;
        return false;
    } //满的话return false
    else {
        for (const Date &date: DoneDates) {
            if (date == today) {
                cout << "今天已打卡过！" << endl;
                return false;
            }
        }
        totalcurrent++;
        wcurrent++;
        DoneDates.push_back(today);
        cout << "第" << currentdoneweek + 1 << "周的第" << wcurrent << "次打卡成功！" << endl;
        checkWeekTask();
        return true;
    } //不满的话检查今天是否已经打卡，已打卡返回false 未打卡+一下天数然后true
}

void WeeklyHabit::display() {
    cout << "[每周习惯]" << name << endl;
    if (completed) cout << "(已完成)";
    cout << "习惯描述:" << description << endl;
    cout << "习惯目标：" << target << "周" << endl;
    cout << "已打卡天数：" << totalcurrent << "天" << endl;
    cout << "总进度：" << currentdoneweek << "周/" << target << "周" << endl;
    cout << "本周打卡进度：" << wcurrent << "次/" << frequency << "次" << endl;
    cout << "最近打卡日期：";
    if (DoneDates.empty()) {
        cout << "无" << endl;
    } else {
        Date &last = DoneDates.back();
        cout << last.year << "-" << last.month << "-" << last.day << endl;
    }
}

void WeeklyHabit::saveToFile(ofstream &out) {
    out << "WeeklyHabit" << endl;
    out << name << endl;
    out << description << endl;
    out << target << endl; //目标周数
    out << frequency << endl; //每周目标次数
    out << currentdoneweek << endl; //已完成打卡周数
    out << wcurrent << endl; //当前周打卡天数
    out << currentweekfirstday.year << " " << currentweekfirstday.month << " " << currentweekfirstday.day << endl;
    //当前周周日
    out << totalcurrent << endl; //总的打卡天数
    out << completed << endl; // 新增：保存完成状态
    for (const Date &date: DoneDates) {
        out << date.year << " " << date.month << " " << date.day << endl;
    } //已完成记录
}

void WeeklyHabit::loadFromFile(ifstream &in) {
    getline(in, name);
    getline(in, description);
    in >> target >> frequency >> currentdoneweek >> wcurrent;
    in.ignore();
    int y, m, d;
    in >> y >> m >> d;
    currentweekfirstday = Date(y, m, d);
    in.ignore();
    in >> totalcurrent;
    in.ignore(); //因为”>>"的输入不会消除换行符，所以得忽略一下换行符
    DoneDates.clear();
    for (int i = 0; i < totalcurrent; ++i) {
        int y, m, d;
        in >> y >> m >> d;
        in.ignore();
        DoneDates.push_back(Date(y, m, d));
    }
}
