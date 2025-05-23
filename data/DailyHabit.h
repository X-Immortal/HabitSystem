//
// Created by xyx on 25-5-23.
//

#ifndef DAILYHABIT_H
#define DAILYHABIT_H

#include <vector>
#include "Date.h"
#include "Habit.h"

using namespace std;

class DailyHabit : public Habit {
public:
    vector<Date> DoneDates;

    DailyHabit();

    DailyHabit(string name1, string d, int T);

    bool complete() override;

    void display() override;

    void saveToFile(ofstream &out) override;

    void loadFromFile(ifstream &in) override;
};

#endif //DAILYHABIT_H
