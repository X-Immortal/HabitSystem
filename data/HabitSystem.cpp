#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>

using namespace std;

struct Date {
    int year;
    int month;
    int day;

    Date(): year(0), month(0), day(0) {
    }

    Date(int y, int m, int d): year(y), month(m), day(d) {
    }

    static Date Ztm(const tm &time) {
        return Date(time.tm_year + 1900, time.tm_mon + 1, time.tm_mday);
    } //将时间转化为Date
    bool operator==(const Date &B) const {
        return (year == B.year && month == B.month && day == B.day);
    } //便于后面判断是否已打卡
    bool operator<=(const Date &B) const {
        if (year != B.year)return (year <= B.year);
        else if (month != B.month)return (month <= B.month);
        else return (day <= B.day);
    }

    static Date today() {
        time_t now = time(0); //获取从纪元到现在的秒数
        tm *today = localtime(&now); //转化为本地时间
        return Ztm(*today);
    } //获取系统当前日期
    static Date Getfirstdayofweek() {
        time_t now = time(0); //获取从纪元到现在的秒数
        tm *lo = localtime(&now); //转化为本地时间
        lo->tm_mday -= lo->tm_wday; //回到每周第一天周日
        mktime(lo);
        return Ztm(*lo);
    }
};

class Habit {
public:
    string name;
    string description;
    int target;
    int totalcurrent;
    bool completed = 0;

    Habit() {
    };

    Habit(string name1, string d, int T): name(name1), description(d), target(T), totalcurrent(0) {
    }

    int gettarget() { return target; };
    int getcurrent() { return totalcurrent; };

    virtual ~Habit() {
    };

    virtual bool complete() =0;

    virtual void display() =0;

    virtual void savetofile(ofstream &out) =0;

    virtual void loadfromfile(ifstream &in) =0;
};

class DailyHabit : public Habit {
public:
    vector<Date> DoneDates;

    DailyHabit() {
    };

    DailyHabit(string name1, string d, int T): Habit(name1, d, T) {
    };

    bool complete() {
        if (completed) {
            cout << "习惯已完成，不能再次打卡！" << endl;
            return false;
        }
        Date today = Date::today();
        for (const Date &date: DoneDates) {
            if (date == today) {
                cout << "今天已打卡过" << endl;
                return false;
            }
        }
        DoneDates.push_back(today);
        totalcurrent++;
        if (totalcurrent >= target) {
            completed = true;
            cout << "恭喜你！" << name << "习惯已完成！" << endl;
        } else {
            cout << "第" << totalcurrent << "次打卡成功！" << endl;
        }
        return true;
    }

    void display() {
        cout << "[每日习惯]" << name << endl;
        if (completed) cout << "(已完成)";
        cout << "习惯描述:" << description << endl;
        cout << "习惯目标：" << target << "天" << endl;
        cout << "已打卡天数：" << totalcurrent << "天" << endl;
        cout << "进度：" << totalcurrent << "天/" << target << "天" << endl;
        cout << "最近打卡日期：";
        if (DoneDates.empty()) {
            cout << "无" << endl;
        } else {
            Date &last = DoneDates.back();
            cout << last.year << "-" << last.month << "-" << last.day << endl;
        }
    }

    void savetofile(ofstream &out) {
        out << "DailyHabit" << endl;
        out << name << endl;
        out << description << endl;
        out << target << endl;
        out << totalcurrent << endl;
        out << completed << endl;
        for (const Date &date: DoneDates) {
            out << date.year << " " << date.month << " " << date.day << endl;
        }
    }

    void loadfromfile(ifstream &in) {
        getline(in, name);
        getline(in, description);
        in >> target >> totalcurrent;
        in.ignore(); //因为”>>"的输入不会消除换行符，所以得忽略一下换行符
        DoneDates.clear();
        for (int i = 0; i < totalcurrent; ++i) {
            int y, m, d;
            in >> y >> m >> d;
            in.ignore();
            DoneDates.push_back(Date(y, m, d));
        }
    }
};

class WeeklyHabit : public Habit {
public:
    int frequency; //每周需要打卡次数
    int currentdoneweek; //已完成打卡周数
    int wcurrent; //当前周打卡次数
    Date currentweekfirstday;
    vector<Date> DoneDates;

    WeeklyHabit() {
    };

    WeeklyHabit(string name1, string d, int WT, int fre): Habit(name1, d, WT), frequency(fre), currentdoneweek(0),
                                                          wcurrent(0),
                                                          currentweekfirstday(Date::today().Getfirstdayofweek()) {
    };

    void checkweektask() {
        if (wcurrent >= frequency) {
            currentdoneweek++;
            cout << "恭喜你！第" << currentdoneweek << "周任务已完成！" << endl;
            if (currentdoneweek >= target) {
                completed = true;
                cout << "恭喜你！" << name << "习惯已完成！" << endl;
            }
        }
    }

    void updatecurweek() {
        Date D1 = Date::today().Getfirstdayofweek();
        if (D1 != currentweekfirstday) {
            if (wcurrent >= frequency) {
                currentdoneweek++;
                cout << "恭喜你！第" << currentdoneweek << "周任务已完成！" << endl;
                if (currentdoneweek >= target) {
                    completed = true;
                    cout << "恭喜你！" << name << "习惯已完成！" << endl;
                }
            } else {
                cout << "上周未达标(" << wcurrent << "/" << frequency << ")！" << endl;
            }
            wcurrent = 0;
            currentweekfirstday = D1;
        }
    } //检查是否为新的一周，若是，则更新
    bool complete() {
        if (completed) {
            cout << "习惯已完成，不能再次打卡！" << endl;
            return false;
        }
        updatecurweek();
        Date today = Date::today();
        if (wcurrent >= frequency) {
            cout << "本周打卡已满！" << endl;
            return false;
        } //满的话return false
        else {
            for (const Date &date: DoneDates) {
                if (date == today) {
                    cout << "今天已打卡过！" << endl;
                    return false;
                }
            }
            totalcurrent++;
            wcurrent++;
            DoneDates.push_back(today);
            cout << "第" << currentdoneweek + 1 << "周的第" << wcurrent << "次打卡成功！" << endl;
            checkweektask();
            return true;
        } //不满的话检查今天是否已经打卡，已打卡返回false 未打卡+一下天数然后true
    }

    void display() {
        cout << "[每周习惯]" << name << endl;
        if (completed) cout << "(已完成)";
        cout << "习惯描述:" << description << endl;
        cout << "习惯目标：" << target << "周" << endl;
        cout << "已打卡天数：" << totalcurrent << "天" << endl;
        cout << "总进度：" << currentdoneweek << "周/" << target << "周" << endl;
        cout << "本周打卡进度：" << wcurrent << "次/" << frequency << "次" << endl;
        cout << "最近打卡日期：";
        if (DoneDates.empty()) {
            cout << "无" << endl;
        } else {
            Date &last = DoneDates.back();
            cout << last.year << "-" << last.month << "-" << last.day << endl;
        }
    }

    void savetofile(ofstream &out) {
        out << "WeeklyHabit" << endl;
        out << name << endl;
        out << description << endl;
        out << target << endl; //目标周数
        out << frequency << endl; //每周目标次数
        out << currentdoneweek << endl; //已完成打卡周数
        out << wcurrent << endl; //当前周打卡天数
        out << currentweekfirstday.year << " " << currentweekfirstday.month << " " << currentweekfirstday.day << endl;
        //当前周周日
        out << totalcurrent << endl; //总的打卡天数
        out << completed << endl; // 新增：保存完成状态
        for (const Date &date: DoneDates) {
            out << date.year << " " << date.month << " " << date.day << endl;
        } //已完成记录
    }

    void loadfromfile(ifstream &in) {
        getline(in, name);
        getline(in, description);
        in >> target >> frequency >> currentdoneweek >> wcurrent;
        in.ignore();
        int y, m, d;
        in >> y >> m >> d;
        currentweekfirstday = Date(y, m, d);
        in.ignore();
        in >> totalcurrent;
        in.ignore(); //因为”>>"的输入不会消除换行符，所以得忽略一下换行符
        DoneDates.clear();
        for (int i = 0; i < totalcurrent; ++i) {
            int y, m, d;
            in >> y >> m >> d;
            in.ignore();
            DoneDates.push_back(Date(y, m, d));
        }
    }
};

class Habitmanager {
private:
    vector<Habit *> Habits;
    string file;

public:
    Habitmanager() {
    };

    Habitmanager(const string &fname): file(fname) {
    };

    ~Habitmanager() {
        for (Habit *habit: Habits) {
            delete habit;
        }
    }

    //添加习惯
    void add(Habit *H) {
        Habits.push_back(H);
    }

    //删除习惯
    void del(string &Habitname) {
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
    vector<Habit *> getDailyHabits() {
        vector<Habit *> result;
        for (Habit *habit: Habits) {
            if (dynamic_cast<DailyHabit *>(habit)) {
                result.push_back(habit);
            }
        }
        return result;
    }

    vector<Habit *> getWeeklyHabits() {
        vector<Habit *> result;
        for (Habit *habit: Habits) {
            if (dynamic_cast<WeeklyHabit *>(habit)) {
                result.push_back(habit);
            }
        }
        return result;
    }

    //打卡习惯
    bool complete(string Habitname) {
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
    void display() {
        cout << "习惯个数为" << Habits.size() << endl;
        for (int i = 0; i < Habits.size(); i++) {
            cout << "[" << i + 1 << "]" << endl;
            Habits[i]->display();
            cout << "----------" << endl;
        }
    }

    //display其中Daily习惯
    void displayD() {
        vector<Habit *> V = getDailyHabits();
        cout << "Daily习惯个数为" << V.size() << endl;
        for (int i = 0; i < V.size(); i++) {
            cout << "[" << i + 1 << "]" << endl;
            V[i]->display();
            cout << "----------" << endl;
        }
    }

    void displayW() {
        vector<Habit *> V = getWeeklyHabits();
        cout << "Weekly习惯个数为" << V.size() << endl;
        for (int i = 0; i < V.size(); i++) {
            cout << "[" << i + 1 << "]" << endl;
            V[i]->display();
            cout << "----------" << endl;
        }
    }

    //文件存储
    void savetofile() {
        ofstream out(file);
        if (!out) {
            cerr << "无法保存文件！" << endl;
            return;
        }
        out << Habits.size() << endl;
        for (Habit *habit: Habits) {
            habit->savetofile(out);
        }
        cout << "数据已保存！" << endl;
    }

    void loadfromfile() {
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
                habit->loadfromfile(in);
                Habits.push_back(habit);
            }
        }
    }

    void showmenu() {
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

    void addHabit() {
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
};

int main() {
    Habitmanager manager("C:\\Users\\15591\\CLionProjects\\untitled2\\habit.txt");
    manager.loadfromfile();
    while (true) {
        manager.showmenu();
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
            case 7: manager.savetofile();
                break;
            case 8: {
                manager.savetofile();
                return 0;
            }
            default: cout << "无效选项" << endl;
        }
    }
    return 0;
}
