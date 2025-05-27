#include <iostream>
#include <fstream>
#include "HabitManager.h"

using namespace std;

int main() {
    HabitManager manager(".\\file\\habits.txt");
    manager.loadFromFile();
    while (true) {
        manager.showMenu();
        int choice;
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1: manager.addHabit();
                break;
            case 2: {
                cout << "请输入要删除的习惯名字：";
                string name;
                cin >> name;
                manager.del(name);
                break;
            }
            case 3: {
                cout << "请输入要打卡的习惯：";
                string name;
                cin >> name;
                manager.complete(name);
                break;
            }
            case 4: manager.display();
                break;
            case 5: manager.displayD();
                break;
            case 6: manager.displayW();
                break;
            case 7: manager.saveToFile();
                break;
            case 8: {
                manager.saveToFile();
                return 0;
            }
            default: cout << "无效选项" << endl;
        }
    }
    return 0;
}
