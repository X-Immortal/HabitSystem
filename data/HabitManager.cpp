//
// Created by xyx on 25-5-23.
//

#include "HabitManager.h"
#include <iostream>
#include "WeeklyHabit.h"
#include "DailyHabit.h"

using namespace std;

HabitManager::HabitManager() {
}

HabitManager::HabitManager(const string &fname): file(fname) {}

HabitManager::~HabitManager() {
    for (Habit *habit: Habits) {
        delete habit;
    }
}

//添加习惯
void HabitManager::add(Habit *H) {
    Habits.push_back(H);
}

//删除习惯
void HabitManager::del(string &Habitname) {
    bool found = false;
    int i = 0;
    while (i < Habits.size()) {
        if (Habits[i]->name == Habitname) {
            delete Habits[i];
            Habits.erase(Habits.begin() + i);
            found = true;
        } else i++;
    }
    if (found) {
        cout << "已删除所有名字为\"" << Habitname << "\"的习惯" << endl;
    } else cout << "未找到该习惯" << endl;
}

//获取Daily/Weekly习惯单独出来的序列
vector<Habit *> HabitManager::getDailyHabits() {
    vector<Habit *> result;
    for (Habit *habit: Habits) {
        if (dynamic_cast<DailyHabit *>(habit)) {
            result.push_back(habit);
        }
    }
    return result;
}

vector<Habit *> HabitManager::getWeeklyHabits() {
    vector<Habit *> result;
    for (Habit *habit: Habits) {
        if (dynamic_cast<WeeklyHabit *>(habit)) {
            result.push_back(habit);
        }
    }
    return result;
}

//打卡习惯
bool HabitManager::complete(string Habitname) {
    int found = 0;
    for (Habit *habit: Habits) {
        if (habit->name == Habitname) {
            found = 1;
            return habit->complete();
        }
    }
    if (found == 0) {
        cout << "未找到该习惯！" << endl;
        return false;
    }
}

//display所有习惯
void HabitManager::display() {
    cout << "习惯个数为" << Habits.size() << endl;
    for (int i = 0; i < Habits.size(); i++) {
        cout << "[" << i + 1 << "]" << endl;
        Habits[i]->display();
        cout << "----------" << endl;
    }
}

//display其中Daily习惯
void HabitManager::displayD() {
    vector<Habit *> V = getDailyHabits();
    cout << "Daily习惯个数为" << V.size() << endl;
    for (int i = 0; i < V.size(); i++) {
        cout << "[" << i + 1 << "]" << endl;
        V[i]->display();
        cout << "----------" << endl;
    }
}

void HabitManager::displayW() {
    vector<Habit *> V = getWeeklyHabits();
    cout << "Weekly习惯个数为" << V.size() << endl;
    for (int i = 0; i < V.size(); i++) {
        cout << "[" << i + 1 << "]" << endl;
        V[i]->display();
        cout << "----------" << endl;
    }
}

//文件存储
void HabitManager::saveToFile() {
    ofstream out(file);
    if (!out) {
        cerr << "无法保存文件！" << endl;
        return;
    }
    out << Habits.size() << endl;
    for (Habit *habit: Habits) {
        habit->saveToFile(out);
    }
    cout << "数据已保存！" << endl;
}

void HabitManager::loadFromFile() {
    ifstream in(file);
    if (!in) {
        // 文件不存在时，创建一个空文件
        ofstream out(file);
        if (!out) {
            cerr << "无法创建文件！" << endl;
            return;
        }
        out << 0 << endl; // 写入0表示没有习惯
        out.close();
        cout << "创建了新文件" << endl;
        return;
    }
    for (Habit *habit: Habits) {
        delete habit;
    }
    Habits.clear();
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
            Habits.push_back(habit);
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
