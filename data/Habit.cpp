//
// Created by xyx on 25-5-23.
//

#include "Habit.h"

Habit::Habit() {}

Habit::Habit(string name1, string d, int T) :
name(name1), description(d), target(T), totalcurrent(0) {}

int Habit::getTarget() {
    return target;
}

int Habit::getCurrent() {
    return totalcurrent;
}

Habit::~Habit() {}