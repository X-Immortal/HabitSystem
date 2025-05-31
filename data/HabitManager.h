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
    static string dataPath;
    static const string setsPath;
    static const string lastTimePath;
    static bool test;
    static Date lastTime;

    struct StaticInitializer {
        StaticInitializer();
    };
    static StaticInitializer initializer;

    HabitManager() = default;

    ~HabitManager();

    static void selectPath();
    static void saveSets();
    static void readSets();
    static void saveHabits();
    static void readLastTime();
    static void saveLastTime();

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

    static string updateWeek();

    //文件存储
    static void save();

    static void load();

    static bool isOnTest();

    static Date getLastTime();

    static void readHabits();
};

#endif //HABITMANAGER_H
