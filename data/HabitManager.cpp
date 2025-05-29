#include "HabitManager.h"
#include "WeeklyHabit.h"
#include "DailyHabit.h"
#include <iostream>
#include <filesystem>

using namespace std;

#if defined(_WIN32)
const string HabitManager::filePath = ".\\.file\\habits.txt";
#else
const string HabitManager::filePath = "./.file/habits.txt";
#endif

vector<Habit *> HabitManager::habits;

HabitManager::StaticInitializer HabitManager::initializer;

HabitManager::StaticInitializer::StaticInitializer() {
    load();
}

HabitManager::~HabitManager() {
    for (Habit *habit: habits) {
        delete habit;
    }
}

//添加习惯
void HabitManager::add(Habit *H) {
    habits.push_back(H);
}

//删除习惯
void HabitManager::del(const string &habitName) {
    for (int i = 0; i < habits.size(); i++) {
        if (habits[i]->getName() == habitName) {
            delete habits[i];
            habits.erase(habits.begin() + i);
            return;
        }
    }
}

//获取Daily/Weekly习惯单独出来的序列
vector<Habit *> HabitManager::getDailyHabits() {
    vector<Habit *> result;
    for (Habit *habit: habits) {
        if (dynamic_cast<DailyHabit *>(habit)) {
            result.push_back(habit);
        }
    }
    return result;
}

vector<Habit *> HabitManager::getWeeklyHabits() {
    vector<Habit *> result;
    for (Habit *habit: habits) {
        if (dynamic_cast<WeeklyHabit *>(habit)) {
            result.push_back(habit);
        }
    }
    return result;
}

vector<Habit *> HabitManager::getHabits() {
    return habits;
}


//打卡习惯
bool HabitManager::checkin(const string &habitName) {
    for (Habit *habit: habits) {
        if (habit->getName() == habitName) {
            return habit->checkin();
        }
    }
    cout << "Habit not found！" << endl;
    return false;
}

//文件存储
void HabitManager::save() {
    filesystem::path path(filePath);
    error_code ec;
    if (!filesystem::create_directories(path.parent_path(), ec) && ec) {
        throw runtime_error("Failed to create directory！");
    }

    ofstream out(filePath);
    if (!out) {
        throw runtime_error("Failed to open file for writing！");
    }
    stringstream ss;
    for (Habit *habit: habits) {
        ss << habit->serialize();
    }
    out << ss.str();
    cout << "File saved!" << endl;
}

void HabitManager::load() {
    filesystem::path path(filePath);
    error_code ec;
    if (!filesystem::create_directories(path.parent_path(), ec) && ec) {
        cerr << "Failed to create directory！" << endl;
        return;
    }

    ifstream in(filePath);
    if (!in) {
        // 文件不存在时，创建一个空文件
        ofstream out(filePath);
        if (!out) {
            throw runtime_error("Failed to create file!");
        }
        cout << "File created!" << endl;
        return;
    }
    for (Habit *habit: habits) {
        delete habit;
    }
    habits.clear();
    stringstream buffer;
    buffer << in.rdbuf();

    // 解析缓冲区内容
    stringstream habitStream;
    string line;
    Habit *habit = nullptr;
    while (getline(buffer, line)) {
        if (line == "[DailyHabit]") {
            habit = new DailyHabit();
        } else if (line == "[WeeklyHabit]") {
            habit = new WeeklyHabit();
        } else {
            throw runtime_error("Invalid file format");
        }

        habitStream << line << endl;

        while (getline(buffer, line)) {
            habitStream << line << endl;
            if (line == "[END]") {
                habit->deserialize(habitStream.str());
                habits.push_back(habit);
                habitStream.str("");
                break;
            }
        }
    }
}
