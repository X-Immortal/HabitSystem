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
    vector<Date> finishedDates;

    DailyHabit();

    DailyHabit(string name, string description, int target);

    bool checkin() override;

    [[nodiscard]] string toString() const override;

    [[nodiscard]] string toSimpleString() const override;

    void saveToFile(ofstream &out) override;

    void loadFromFile(ifstream &in) override;
};

#endif //DAILYHABIT_H
