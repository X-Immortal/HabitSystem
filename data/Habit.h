//
// Created by xyx on 25-5-23.
//

#ifndef HABIT_H
#define HABIT_H

#include <fstream>

using namespace std;

class Habit {
public:
    string name;
    string description;
    int target;
    int totalcurrent;
    bool completed = 0;

    Habit();

    Habit(string name1, string d, int T);

    int getTarget();

    int getCurrent();

    virtual ~Habit();

    virtual bool complete() = 0;

    virtual void display() = 0;

    virtual void saveToFile(ofstream &out) = 0;

    virtual void loadFromFile(ifstream &in) = 0;
};

#endif //HABIT_H
