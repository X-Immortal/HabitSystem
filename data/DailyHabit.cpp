//
// Created by xyx on 25-5-23.
//

#include "DailyHabit.h"
#include "../tools/StringUtil.h"
#include <iostream>
#include <sstream>

DailyHabit::DailyHabit() {
}

DailyHabit::DailyHabit(string name, string description, int target): Habit(name, description, target) {
}

bool DailyHabit::checkin() {
    if (isCompleted()) {
        cerr << "Habit finished！" << endl;
        return false;
    }
    if (checkedInToday()) {
        cout << "You have checked in today!" << endl;
        return false;
    }
    Date today = Date::today();
    finishedDates.push_back(today);
    finishedDays++;
    return true;
}

QString DailyHabit::toString() const {
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
                "       目标天数：%4<br/>"
                "       已打卡天数：%5<br/>"
                "       历史打卡日期：%6"
                "   </p>"
                "</html>"
            )
            .arg(
                isCompleted() ? "(已完成)" : "",
                name,
                description,
                QString::number(target),
                QString::number(finishedDays),
                historyDates.str()
            );
}

QString DailyHabit::toSimpleString() const {
    QString qname = QString::fromUtf8(name.c_str());
    return QString(
                "<html>"
                "   <p>"
                "       [每日习惯]%1<br/>"
                "       名称：%2<br/>"
                "       进度(天)：%3/%4<br/>"
                "       上次打卡日期：%5"
                "   </p>"
                "</html>"
            )
            .arg(
                isCompleted() ? "(已完成)" : "",
                qname.length() > 5 ? qname.left(5) + "..." : qname,
                QString::number(finishedDays), QString::number(target),
                finishedDates.empty() ? "无" : "<br/>" + finishedDates.back().toString()
            );
}

string DailyHabit::serialize() {
    stringstream out;
    out << "[DailyHabit]" << endl
            << "name=" << name << endl
            << "description=" << StringUtil::escape(description) << endl
            << "target=" << target << endl
            << "finishedDays=" << finishedDays << endl
            << "[DATES]" << endl;
    for (const Date &date: finishedDates) {
        out << date.getYear() << " " << date.getMonth() << " " << date.getDay() << endl;
    }
    out << "[END]" << endl;
    return out.str();
}

void DailyHabit::deserialize(const string &data) {
    istringstream in(data);
    string line;
    getline(in, line);
    if (line != "[DailyHabit]") {
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
        } else if (k == "finishedDays") {
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
