//
// Created by xyx on 25-5-23.
//

#ifndef HABIT_H
#define HABIT_H

#include <fstream>

using namespace std;

class Habit {
protected:
    string name;
    string description;
    int target;
    int finishedDays;
    bool completed = false;

    Habit();

    Habit(string name, string description, int target);

public:
    [[nodiscard]] string getName() const;

    [[nodiscard]] string getDescription() const;

    [[nodiscard]] int getTarget() const;

    [[nodiscard]] int getFinishedDays() const;

    [[nodiscard]] bool isCompleted() const;

    virtual ~Habit() = default;

    virtual bool checkin() = 0;

    [[nodiscard]] virtual string toString() const = 0;

    virtual void saveToFile(ofstream &out) = 0;

    virtual void loadFromFile(ifstream &in) = 0;

};

#endif //HABIT_H
