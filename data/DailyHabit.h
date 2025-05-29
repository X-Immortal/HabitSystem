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
    vector<Date> finishedDates;

public:
    DailyHabit();

    DailyHabit(string name, string description, int target);

    bool checkin() override;

    [[nodiscard]] QString toString() const override;

    [[nodiscard]] QString toSimpleString() const override;

    string serialize() override;

    void deserialize(const string &data) override;
};

#endif //DAILYHABIT_H
