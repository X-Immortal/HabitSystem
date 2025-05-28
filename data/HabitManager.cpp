#include "HabitManager.h"
#include "WeeklyHabit.h"
#include "DailyHabit.h"
#include <iostream>
#include <filesystem>

using namespace std;

#if defined(_WIN32)
const string HabitManager::file = ".\\file\\habits.txt";
#else
const string HabitManager::filePath = "./file/habits.txt";
#endif

vector<Habit *> HabitManager::habits;

HabitManager::StaticInitializer HabitManager::initializer;

HabitManager::StaticInitializer::StaticInitializer() {
    loadFromFile();
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
    bool found = false;
    int i = 0;
    while (i < habits.size()) {
        if (habits[i]->getName() == habitName) {
            delete habits[i];
            habits.erase(habits.begin() + i);
            found = true;
        } else i++;
    }
    if (found) {
        cout << "已删除所有名字为\"" << habitName << "\"的习惯" << endl;
    } else cout << "未找到该习惯" << endl;
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
bool HabitManager::checkin(const string& habitName) {
    for (Habit *habit: habits) {
        if (habit->getName() == habitName) {
            return habit->checkin();
        }
    }
    cout << "未找到该习惯！" << endl;
    return false;
}

//文件存储
void HabitManager::saveToFile() {
    filesystem::path path(filePath);
    if (!filesystem::create_directories(path.parent_path())) {
        cerr << "无法创建目录！" << endl;
        return;
    }

    ofstream out(filePath);
    if (!out) {
        cerr << "无法保存文件！" << endl;
        return;
    }
    out << habits.size() << endl;
    for (Habit *habit: habits) {
        habit->saveToFile(out);
    }
    cout << "数据已保存！" << endl;
}

void HabitManager::loadFromFile() {
    filesystem::path path(filePath);
    error_code ec;
    if (!filesystem::create_directories(path.parent_path(), ec) && ec) {
        cerr << "无法创建目录！" << endl;
        return;
    }

    ifstream in(filePath);
    if (!in) {
        // 文件不存在时，创建一个空文件
        ofstream out(filePath);
        if (!out) {
            cerr << "无法创建文件！" << endl;
            return;
        }
        out << 0 << endl; // 写入0表示没有习惯
        out.close();
        cout << "创建了新文件" << endl;
        return;
    }
    for (Habit *habit: habits) {
        delete habit;
    }
    habits.clear();
    int count;
    in >> count;
    in.ignore();
    for (int i = 0; i < count; ++i) {
        string type;
        getline(in, type);
        Habit *habit = nullptr;
        if (type == "DailyHabit")
            habit = new DailyHabit();
        else if (type == "WeeklyHabit")
            habit = new WeeklyHabit();
        if (habit) {
            habit->loadFromFile(in);
            habits.push_back(habit);
        }
    }
}

void HabitManager::showMenu() {
    cout << "=====习惯管理=====" << endl;
    cout << "1、添加习惯" << endl;
    cout << "2、删除习惯" << endl;
    cout << "3、打卡" << endl;
    cout << "4、查看所有习惯" << endl;
    cout << "5、查看Daily习惯" << endl;
    cout << "6、查看Weekly习惯" << endl;
    cout << "7、保存数据" << endl;
    cout << "8、退出程序" << endl;
}

void HabitManager::addHabit() {
    string name, d, type;
    int T, fre;
    cout << "请输入习惯名称：";
    getline(cin, name);
    cout << "请输入习惯描述：";
    getline(cin, d);
    while (true) {
        cout << "选择习惯类型（D-Daily,W-Weekly)";
        getline(cin, type);
        if (type == "D" || type == "d") {
            cout << "请输入目标天数：";
            cin >> T;
            add(new DailyHabit(name, d, T));
            cout << "习惯添加成功！" << endl;
            break;
        } else if (type == "W" || type == "w") {
            cout << "请输入目标周数：";
            cin >> T;
            cout << "请输入每周打卡次数：";
            cin >> fre;
            add(new WeeklyHabit(name, d, T, fre));
            cout << "习惯添加成功！" << endl;
            break;
        } else {
            cout << "输入错误！请重新输入！" << endl;
        }
    }
}
