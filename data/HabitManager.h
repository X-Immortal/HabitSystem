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
    static vector<Habit *> habits;
    static const string filePath;

    struct StaticInitializer {
        StaticInitializer();
    };
    static StaticInitializer initializer;

    HabitManager() = default;

    ~HabitManager();

public:
    //添加习惯
    static void add(Habit *H);

    //删除习惯
    static void del(const string &habitName);

    //获取Daily/Weekly习惯单独出来的序列
    static vector<Habit *> getDailyHabits();

    static vector<Habit *> getWeeklyHabits();

    static vector<Habit *> getHabits();

    //打卡习惯
    static bool checkin(const string &habitName);

    //文件存储
    static void saveToFile();

    static void loadFromFile();

    static void showMenu();

    static void addHabit();
};

#endif //HABITMANAGER_H
