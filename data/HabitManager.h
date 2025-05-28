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
    static vector<Habit *> Habits;
    static string file;

public:
    HabitManager();

    ~HabitManager();

    //添加习惯
    static void add(Habit *H);

    //删除习惯
    static void del(string &Habitname);

    //获取Daily/Weekly习惯单独出来的序列
    static vector<Habit *> getDailyHabits();

    static vector<Habit *> getWeeklyHabits();

    //打卡习惯
    static bool checkin(string Habitname);

    //display所有习惯
    void display();

    //display其中Daily习惯
    void displayD();

    void displayW();

    //文件存储
    static void saveToFile();

    static void loadFromFile();

    static void showMenu();

    static void addHabit();
};

#endif //HABITMANAGER_H
