#include "HabitManager.h"
#include "WeeklyHabit.h"
#include "DailyHabit.h"
#include "../tools/StringUtil.h"
#include <iostream>
#include <filesystem>
#include <sstream>

using namespace std;

#if defined(_WIN32)
string HabitManager::dataPath = "..\\.file\\data\\normal\\habits.txt";
const string HabitManager::setsPath = "..\\.file\\sets\\test.properties";
const string HabitManager::lastTimePath = "..\\.file\\data\\normal\\lasttime.txt";
#else
string HabitManager::filePath = "../.file/data/habits.txt";
const string HabitManager::setsPath = "../.file/sets/test.properties";
const string HabitManager::lastTimePath = "../.file/data/normal/lasttime.txt";
#endif

vector<Habit *> HabitManager::habits;
bool HabitManager::test = false;
Date HabitManager::lastTime = Date::today();

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
    lastTime = Date::today();
    saveSets();
    saveLastTime();
    saveHabits();
}

void HabitManager::saveHabits() {
    selectPath();
    error_code ec;
    filesystem::path fdataPath(dataPath);
    if (!filesystem::create_directories(fdataPath.parent_path(), ec) && ec) {
        cerr << "Failed to create directory！" << endl;
        return;
    }
    ofstream out(dataPath);
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
    readSets();
    readLastTime();
    readHabits();
}

void HabitManager::readHabits() {
    selectPath();
    error_code ec;
    filesystem::path fdataPath(dataPath);
    if (!filesystem::create_directories(fdataPath.parent_path(), ec) && ec) {
        cerr << "Failed to create directory！" << endl;
        return;
    }

    ifstream in(dataPath);
    if (!in) {
        // 文件不存在时，创建一个空文件
        ofstream out(dataPath);
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


string HabitManager::updateWeek() {
    stringstream ss;
    ss << "<html><p>上周达标任务：";
    for (Habit *habit: getWeeklyHabits()) {
        WeeklyHabit *weeklyHabit = dynamic_cast<WeeklyHabit *>(habit);
        try {
            if (weeklyHabit->isCompletedThisWeek()) {
                ss << "<br/>" << weeklyHabit->updateWeek();
            } else {
                weeklyHabit->updateWeek();
            }
        } catch (runtime_error &e) {
            if (strcmp(e.what(), "no new week") == 0) {
                throw;
            }
        }
    }
    ss << "</p></html>";
    string result = ss.str();
    if (result == "<html><p>上周达标任务：</p></html>") {
        return "<html><p>上周无达标任务</p></html>";
    }
    return ss.str();
}

void HabitManager::selectPath() {
    if (Date::canModify()) {
        dataPath =
#ifdef _WIN32
                "..\\.file\\data\\test\\habits.txt";
#else
            "../file/data/test/habits.txt";
#endif
    } else {
        dataPath =
#ifdef _WIN32
                "..\\.file\\data\\normal\\habits.txt";
#else
                "../file/data/normal/habits.txt";
#endif
    }
}

void HabitManager::saveSets() {
    ofstream out(setsPath);
    if (!out) {
        throw runtime_error("Failed to open file for writing！");
    }
    out << "test=" << (test ? "true" : "false") << endl << "today=";
    if (!test) {
        out << "today";
        cout << "Sets saved!" << endl;
        return;
    }
    if (Date::canModify()) {
        Date atoday = Date::today();
        out << atoday.getYear() << " " << atoday.getMonth() << " " << atoday.getDay();
    } else {
        out << "today";
    }
    cout << "Sets saved!" << endl;
}


void HabitManager::readSets() {
    error_code ec;
    filesystem::path fsetsPath(setsPath);
    if (!filesystem::create_directories(fsetsPath.parent_path(), ec) && ec) {
        throw runtime_error("Failed to create directory！");
    }

    ifstream in(setsPath);
    if (!in) {
        // 文件不存在时，创建一个空文件
        ofstream out(setsPath);
        if (!out) {
            throw runtime_error("Failed to create file!");
        }
        out << "test=false" << endl << "today=today" << endl;
        cout << "File created!" << endl;
        return;
    }

    stringstream buffer;
    buffer << in.rdbuf();
    string line;
    getline(buffer, line);
    if (line != "test=true" && line != "test=false") {
        throw runtime_error("Invalid sets");
    }
    if (!(test = line.ends_with("true"))) {
        return;
    }
    getline(buffer, line);
    vector<string> kv = StringUtil::split(line, '=');
    if (kv.size() != 2 || kv[0] != "today") {
        throw runtime_error("Invalid sets");
    }
    if (kv[1] != "today") {
        Date::setModifiable(true);
        buffer = stringstream(kv[1]);
        int y, m, d;
        buffer >> y >> m >> d;
        Date::setToday(y, m, d);
    }
}

bool HabitManager::isOnTest() {
    return test;
}

void HabitManager::readLastTime() {
    if (Date::canModify()) {
        lastTime = Date::today();
    } else {
        error_code ec;
        filesystem::path fsetsPath(lastTimePath);
        if (!filesystem::create_directories(fsetsPath.parent_path(), ec) && ec) {
            throw runtime_error("Failed to create directory！");
        }

        ifstream in(lastTimePath);
        if (!in) {
            // 文件不存在时，创建一个空文件
            ofstream out(setsPath);
            if (!out) {
                throw runtime_error("Failed to create file!");
            }
            Date atoday = Date::today();
            out << atoday.getYear() << " " << atoday.getMonth() << " " << atoday.getDay() << endl;
            cout << "File created!" << endl;
            return;
        }

        int y, m, d;
        in >> y >> m >> d;
        lastTime = Date(y, m, d);
    }
}

void HabitManager::saveLastTime() {
    if (Date::canModify()) {
        return;
    }
    ofstream out(lastTimePath);
    if (!out) {
        throw runtime_error("Failed to open file for writing！");
    }
    out << lastTime.getYear() << " " << lastTime.getMonth() << " " << lastTime.getDay();
    cout << "Last time saved!" << endl;
}

Date HabitManager::getLastTime() {
    return lastTime;
}