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
    int finishedWeeks; //已完成打卡周数
    int checkinTimes; //当前周打卡次数
    Date firstDayOfThisWeek;
    vector<Date> finishedDates;

    WeeklyHabit();

    WeeklyHabit(string name, string description, int target, int frequency);

    void checkWeekTask();

    void updateCurrentWeek(); //检查是否为新的一周，若是，则更新

    bool checkin() override;

    [[nodiscard]] string toString() const override;

    void saveToFile(ofstream &out) override;

    void loadFromFile(ifstream &in) override;
};

#endif //WEEKLYHABIT_H
