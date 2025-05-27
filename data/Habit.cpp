//
// Created by xyx on 25-5-23.
//

#include "Habit.h"

Habit::Habit() {}

Habit::Habit(string name, string description, int target) :
name(name), description(description), target(target), totalcurrent(0) {}

int Habit::getTarget() {
    return target;
}

int Habit::getCurrent() {
    return totalcurrent;
}

Habit::~Habit() {}