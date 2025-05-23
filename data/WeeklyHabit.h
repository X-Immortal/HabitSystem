//
// Created by xyx on 25-5-23.
//

#ifndef WEEKLYHABIT_H
#define WEEKLYHABIT_H

#include "Date.h"
#include "Habit.h"
#include <vector>

using namespace std;

class WeeklyHabit : public Habit {
public:
    int frequency; //每周需要打卡次数
    int currentdoneweek; //已完成打卡周数
    int wcurrent; //当前周打卡次数
    Date currentweekfirstday;
    vector<Date> DoneDates;

    WeeklyHabit();

    WeeklyHabit(string name1, string d, int WT, int fre);

    void checkWeekTask();

    void updateCurweek(); //检查是否为新的一周，若是，则更新

    bool complete() override;

    void display() override;

    void saveToFile(ofstream &out) override;

    void loadFromFile(ifstream &in) override;
};

#endif //WEEKLYHABIT_H
