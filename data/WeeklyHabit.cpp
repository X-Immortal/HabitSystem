//
// Created by xyx on 25-5-23.
//

#include "WeeklyHabit.h"
#include <iostream>
#include <sstream>
#include "../tools/StringUtil.h"

WeeklyHabit::WeeklyHabit() : frequency(0), finishedWeeks(0), finishedDaysThisWeek(0) {}

WeeklyHabit::WeeklyHabit(string name, string description, int target, int frequency):
    Habit(name, description, target), frequency(frequency), finishedWeeks(0), finishedDaysThisWeek(0)
{}

bool WeeklyHabit::isCompletedThisWeek() const {
    return finishedDaysThisWeek >= frequency;
}

bool WeeklyHabit::canCheckin() const {
    return Habit::canCheckin() && !isCompletedThisWeek();
}

string WeeklyHabit::updateWeek() {
    if (Date::newWeek()) {
        if (isCompletedThisWeek()) {
            finishedWeeks++;
            stringstream ss;
            ss << name << "(" << finishedDaysThisWeek << "/" << frequency << ")";
            return ss.str();
        }
        finishedDaysThisWeek = 0;
    }
    return "";
} //检查是否为新的一周，若是，则更新

bool WeeklyHabit::checkin() {
    if (!canCheckin()) {
        return false;
    }
    Date today = Date::today();
    finishedDays++;
    finishedDaysThisWeek++;
    finishedDates.push_back(today);
    return true;
    //不满的话检查今天是否已经打卡，已打卡返回false 未打卡+一下天数然后true
}

QString WeeklyHabit::toString() const {
    stringstream historyDates;
    if (finishedDates.empty()) {
        historyDates << "无";
    } else {
        for (int i = finishedDates.size() - 1; i >= 0; --i) {
            historyDates << "<br/>" << finishedDates[i].toString();
        }
    }
    return QString(
        "<html>"
        "   <p>"
        "       [每日习惯]%1<br/>"
        "       习惯名称：<br/>%2<br/>"
        "       习惯描述：<br/>%3<br/>"
        "       目标周数：%4<br/>"
        "       目标频率：%5<br/>"
        "       已完成周数：%6<br/>"
        "       本周已打卡次数：%7<br/>"
        "       已打卡天数：%8<br/>"
        "       历史打卡日期：%9"
        "   </p>"
        "</html>"
        )
        .arg(
            isCompleted() ? "(已完成)" : "",
            name,
            description,
            QString::number(target),
            QString::number(frequency),
            QString::number(finishedWeeks),
            QString::number(finishedDaysThisWeek),
            QString::number(finishedDays),
            historyDates.str()
        );
}

QString WeeklyHabit::toSimpleString() const {
    QString qname = QString::fromUtf8(name.c_str());
    return QString(
        "<html>"
        "   <p>"
        "       [每周习惯]%1<br/>"
        "       名称：%2<br/>"
        "       本周进度(天)：%3/%4<br/>"
        "       总进度(周)：%5/%6<br/>"
        "       上次打卡日期：%7"
        "   </p>"
        "</html>"
        )
        .arg(
            isCompleted() ? "(已完成)" : "",
            qname.length() > 5 ? qname.left(5) + "..." : qname,
            QString::number(finishedDaysThisWeek), QString::number(target),
            QString::number(finishedWeeks), QString::number(target),
            finishedDates.empty() ? "无" : "<br/>" + finishedDates.back().toString()
        );
}


string WeeklyHabit::serialize() {
    stringstream out;
    out << "[WeeklyHabit]" << endl
        << "name=" << name << endl
        << "description=" << StringUtil::escape(description) << endl
        << "target=" << target << endl //目标周数
        << "frequency=" << frequency << endl //每周目标次数
        << "finishedWeeks=" << finishedWeeks << endl //已完成打卡周数
        << "finishedDaysThisWeek=" << finishedDaysThisWeek << endl //当前周打卡天数
        << "finishedDays=" << finishedDays << endl //总的打卡天数
        << "[DATES]" << endl;
    for (const Date &date: finishedDates) {
        out << date.getYear() << " " << date.getMonth() << " " << date.getDay() << endl;
    } //已完成记录
    out << "[END]" << endl;
    return out.str();
}

void WeeklyHabit::deserialize(const string &data) {
    istringstream in(data);
    string line;
    getline(in, line);
    if (line != "[WeeklyHabit]") {
        throw runtime_error("Invalid data");
    }

    while (getline(in, line)) {
        if (line.empty()) {
            continue;
        }

        if (line == "[DATES]") {
            break;
        }

        vector<string> kv = StringUtil::split(line, '=');
        if (kv.size() != 2) {
            throw runtime_error("Invalid data");
        }
        string k = kv[0];
        string v = kv[1];
        if (k == "name") {
            name = v;
        } else if (k == "description") {
            description = StringUtil::unescape(v);
        } else if (k == "target") {
            target = stoi(v);
        } else if (k == "frequency") {
            frequency = stoi(v);
        } else if (k == "finishedWeeks") {
            finishedWeeks = stoi(v);
        } else if (k == "finishedDaysThisWeek") {
            finishedDaysThisWeek = stoi(v);
        }else if (k == "finishedDays") {
            finishedDays = stoi(v);
        } else {
            throw runtime_error("Invalid data");
        }
    }
    for (int i = 0; i < finishedDays; ++i) {
        int y, m, d;
        in >> y >> m >> d;
        in.ignore();
        finishedDates.push_back(Date(y, m, d));
    }
    sort(finishedDates.begin(), finishedDates.end());
    getline(in, line);
    if (line != "[END]") {
        throw runtime_error("Invalid data");
    }
}
