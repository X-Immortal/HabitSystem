#include "Habit.h"

Habit::Habit() {}

Habit::Habit(string name, string description, int target) :
name(name), description(description), target(target), finishedDays(0) {}

string Habit::getName() const {
    return name;
}

string Habit::getDescription() const {
    return description;
}

int Habit::getTarget() const {
    return target;
}

int Habit::getFinishedDays() const {
    return finishedDays;
}

bool Habit::isCompleted() const {
    return finishedDays >= target;
}