//
// Created by xyx on 25-5-23.
//

#ifndef HABITMANAGER_H
#define HABITMANAGER_H

#include <vector>
#include "Habit.h"

using namespace std;

class HabitManager {
private:
    vector<Habit *> Habits;
    string file;

public:
    HabitManager();

    HabitManager(const string &fname);

    ~HabitManager();

    //添加习惯
    void add(Habit *H);

    //删除习惯
    void del(string &Habitname);

    //获取Daily/Weekly习惯单独出来的序列
    vector<Habit *> getDailyHabits();

    vector<Habit *> getWeeklyHabits();

    //打卡习惯
    bool complete(string Habitname);

    //display所有习惯
    void display();

    //display其中Daily习惯
    void displayD();

    void displayW();

    //文件存储
    void saveToFile();

    void loadFromFile();

    void showMenu();

    void addHabit();
};

#endif //HABITMANAGER_H
