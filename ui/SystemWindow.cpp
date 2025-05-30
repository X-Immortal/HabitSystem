//
// Created by xyx on 25-5-22.
//
#include "SystemWindow.h"

#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include "PushButton.h"
#include <QDate>
#include <QScrollArea>
#include <QSizePolicy>
#include <QHBoxLayout>
#include "../data/HabitManager.h"
#include "CheckinSucceededDialog.h"
#include "AddDialog.h"
#include "DeleteDialog.h"
#include "WeeklyAchievementDialog.h"

SystemWindow::SystemWindow(QWidget *parent) : QMainWindow(parent) {
    initWindow();
    initDialog();
    initText();
    initButton();
    initScrollArea();
    loadCards();
}

void SystemWindow::initWindow() {
    setWindowTitle("习惯打卡管理系统");
    setFixedSize(700, 500);
    setAttribute(Qt::WA_DeleteOnClose);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    centralWidget->setFixedSize(this->width(), this->height());
    centralWidget->setStyleSheet("background-color: #e3e3e3;");
}

void SystemWindow::initText() {
    QWidget *textContainer = new QWidget(this);
    textContainer->setGeometry(0, 45, width(), 90);
    textContainer->setStyleSheet("background: transparent;");

    QVBoxLayout *textLayout = new QVBoxLayout(textContainer);
    textLayout->setSpacing(10);
    textLayout->setContentsMargins(0, 0, 0, 0);
    textContainer->setLayout(textLayout);

    QLabel *title = new QLabel("习惯打卡管理系统", centralWidget());
    title->setStyleSheet("QLabel { font: bold 40px; color: black; background: transparent; }");
    title->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    title->setAlignment(Qt::AlignCenter);
    textLayout->addWidget(title);

    QPushButton *nowtime = new QPushButton("今天是" + QString::fromStdString(today.toString()), centralWidget());
    nowtime->setStyleSheet("QPushButton { font: 20px; color: black; background: transparent; border: 0px; } QPushButton:hover { background: transparent; }");
    nowtime->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(nowtime, &QPushButton::clicked, this, [=] {
        cout << "nowtime clicked!" << endl;
    });
    textLayout->addWidget(nowtime);
}


void SystemWindow::initButton() {
    QWidget *buttonContainer = new QWidget(this);
    buttonContainer->setGeometry(580, 150, 80, 300);
    buttonContainer->setStyleSheet("background: transparent;");

    QVBoxLayout *buttonLayout = new QVBoxLayout(buttonContainer);
    buttonLayout->setSpacing(20);
    buttonLayout->setContentsMargins(0, 0, 0, 0);
    buttonContainer->setLayout(buttonLayout);

    QString styleSheet = "QPushButton { font-size: 20px; font: Times-New-Roman; border-radius: 40px; }";

    PushButton *allButton = new PushButton("All", centralWidget());
    allButton->addStyle(styleSheet);
    allButton->setFixedSize(80, 80);
    connect(allButton, &QPushButton::clicked, this, [=]() {
        state = ALL;
        loadCards();
    });
    buttonLayout->addWidget(allButton);

    PushButton *dailyButton = new PushButton("Daily", centralWidget());
    dailyButton->addStyle(styleSheet);
    dailyButton->setFixedSize(80, 80);
    connect(dailyButton, &QPushButton::clicked, this, [=]() {
        state = DAILY;
        loadCards();
    });
    buttonLayout->addWidget(dailyButton);

    PushButton *weeklyButton = new PushButton("Weekly", centralWidget());
    weeklyButton->addStyle(styleSheet);
    weeklyButton->setFixedSize(80, 80);
    connect(weeklyButton, &QPushButton::clicked, this, [=]() {
        state = WEEKLY;
        loadCards();
    });
    buttonLayout->addWidget(weeklyButton);
}

void SystemWindow::closeEvent(QCloseEvent *event) {
    HabitManager::save();
    qApp->quit();
}

void SystemWindow::initScrollArea() {
    QScrollArea *scrollArea = new QScrollArea(centralWidget());
    scrollArea->setWidgetResizable(true);
    scrollArea->setGeometry(80, 150, 490, 300);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setStyleSheet("QScrollArea { border: 1px solid black; background: transparent; }");

    scrollContainer = new QWidget(scrollArea);
    scrollContainer->setFixedHeight(scrollArea->height() - 10);
    scrollContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    scrollArea->setWidget(scrollContainer);

    QHBoxLayout *scrollLayout = new QHBoxLayout(scrollContainer);
    scrollLayout->setSpacing(20);
    scrollContainer->setLayout(scrollLayout);

    connect(addDialog, &AddDialog::habitAdded, this, [=] {
        loadCards();
    });
}

void SystemWindow::addCard(Habit *habit) {
    QLabel *habitLabel = new QLabel(
        habit->toSimpleString(),
        scrollContainer
    );
    habitLabel->setStyleSheet(
        "QLabel {"
        "   font: 15px;"
        "   color: #000000;"
        "   background: silver;"
        "   border: 1px solid #000000;"
        "}"
    );
    habitLabel->setFixedSize(150, 250);
    habitLabel->setWordWrap(true);
    scrollContainer->layout()->addWidget(habitLabel);

    QWidget *buttonContainer = new QWidget(habitLabel);
    buttonContainer->setStyleSheet("background: transparent;");
    buttonContainer->setGeometry(0, 210, habitLabel->width(), 25);

    QHBoxLayout *buttonLayout = new QHBoxLayout(buttonContainer);
    buttonLayout->setContentsMargins(0, 0, 0, 0);
    buttonContainer->setLayout(buttonLayout);

    if (habit->canCheckin()) {
        PushButton *checkinButton = new PushButton("打卡", habitLabel);
        checkinButton->addStyle("QPushButton{ font: bold 15px; }");
        checkinButton->setFixedSize(50, 25);
        connect(checkinButton, &QPushButton::clicked, this, [=]() {
            checkinDialog->show(habit);
        });
        buttonLayout->addWidget(checkinButton);
    }


    PushButton *deleteButton = new PushButton("删除", habitLabel);
    deleteButton->addStyle("QPushButton{ font: bold 15px; }");
    deleteButton->setFixedSize(50, 25);
    connect(deleteButton, &QPushButton::clicked, this, [=] {
        deleteDialog->show(habit);
    });
    buttonLayout->addWidget(deleteButton);

    PushButton *infoButton = new PushButton("详情", habitLabel);
    infoButton->addStyle("QPushButton{ font: bold; }");
    infoButton->setGeometry(100, 20, 40, 15);
    connect(infoButton, &QPushButton::clicked, this, [=]() {
        informationDialog->show(habit);
    });
}

void SystemWindow::clearCards() {
    QList<QWidget *> childWidgets = scrollContainer->findChildren<QWidget *>();
    for (QWidget *widget: childWidgets) {
        widget->deleteLater();
    }
}

void SystemWindow::loadCards() {
    vector<Habit *> habits;
    switch (state) {
        case ALL:
            habits = HabitManager::getHabits();
            break;
        case DAILY:
            habits = HabitManager::getDailyHabits();
            break;
        case WEEKLY:
            habits = HabitManager::getWeeklyHabits();
            break;
        default:
            break;
    }

    clearCards();

    for (int i = 0; i < habits.size(); ++i) {
        addCard(habits[i]);
    }

    QPushButton *addButton = new QPushButton("+", scrollContainer);
    addButton->setFixedSize(150, 200);
    addButton->setStyleSheet(
        "QPushButton {"
        "   font: 90px;"
        "   color: #000000;"
        "   background: #1e2f0c;"
        "   border: 1px solid #000000;"
        "   padding: 0px;"
        "   text-align: center;"
        "}"
    );
    connect(addButton, &QPushButton::clicked, this, [=] {
        addDialog->show();
    });
    scrollContainer->layout()->addWidget(addButton);
}

void SystemWindow::initDialog() {
    addDialog = new AddDialog(this);
    deleteDialog = new DeleteDialog(this);
    informationDialog = new InformationDialog(this);
    checkinDialog = new CheckinDialog(this);
    checkinSucceededDialog = new CheckinSucceededDialog(this);
    connect(checkinDialog, &CheckinDialog::checkinConfirmed, this, [=](Habit *habit) {
        habit->checkin();
        loadCards();
        checkinSucceededDialog->show(habit->isCompleted());
    });
    connect(deleteDialog, &DeleteDialog::deleteConfirmed, this, [=](Habit *habit) {
        HabitManager::del(habit->getName());
        loadCards();
    });

    if (Date::newWeek()) {
        WeeklyAchievementDialog *weeklyAchievementDialog = new WeeklyAchievementDialog(this);
        weeklyAchievementDialog->show();
    }
}
