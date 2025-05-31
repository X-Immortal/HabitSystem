//
// Created by xyx on 25-5-23.
//

#ifndef HABIT_H
#define HABIT_H

#include <fstream>
#include <QString>
#include "../tools/Date.h"

using namespace std;

class Habit {
protected:
    string name;
    string description;
    int target;
    int finishedDays;
    vector<Date> finishedDates;

    Habit();

    Habit(string name, string description, int target);

public:
    [[nodiscard]] string getName() const;

    [[nodiscard]] string getDescription() const;

    [[nodiscard]] int getTarget() const;

    [[nodiscard]] int getFinishedDays() const;

    [[nodiscard]] virtual bool isCompleted() const;

    [[nodiscard]] bool checkedInToday() const;

    [[nodiscard]] virtual bool canCheckin() const;

    virtual ~Habit() = default;

    virtual bool checkin() = 0;

    [[nodiscard]] virtual QString toString() const = 0;

    [[nodiscard]] virtual QString toSimpleString() const = 0;

    virtual string serialize() = 0;

    virtual void deserialize(const string &data) = 0;
};

#endif //HABIT_H
