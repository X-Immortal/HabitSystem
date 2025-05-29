//
// Created by xyx on 25-5-22.
//
#include "SystemWindow.h"
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
    QLabel *title = new QLabel("习惯打卡管理系统", centralWidget());
    title->setStyleSheet(
        "QLabel {"
        "   font: bold 40px;"
        "   color: #000000;"
        "   background: transparent;"
        "}"
    );
    title->setGeometry(190, 50, 350, 50);

    QLabel *nowtime = new QLabel("今天是" + QDate::currentDate().toString("yyyy年MM月dd日"), centralWidget());
    nowtime->setStyleSheet(
        "QLabel {"
        "   font: 20px;"
        "   color: #000000;"
        "   background: transparent;"
        "}"
    );
    nowtime->setGeometry(240, 110, 210, 30);
}


void SystemWindow::initButton() {
    QString styleSheet = "QPushButton { font-size: 20px; font: Times-New-Roman; border-radius: 40px; }";

    PushButton *allButton = new PushButton("All", centralWidget());
    allButton->addStyle(styleSheet);
    allButton->setGeometry(550, 160, 80, 80);
    connect(allButton, &QPushButton::clicked, this, [=]() {
        state = ALL;
        loadCards();
    });

    PushButton *dailyButton = new PushButton("Daily", centralWidget());
    dailyButton->addStyle(styleSheet);
    dailyButton->setGeometry(550, 260, 80, 80);
    connect(dailyButton, &QPushButton::clicked, this, [=]() {
        state = DAILY;
        loadCards();
    });

    PushButton *weeklyButton = new PushButton("Weekly", centralWidget());
    weeklyButton->addStyle(styleSheet);
    weeklyButton->setGeometry(550, 360, 80, 80);
    connect(weeklyButton, &QPushButton::clicked, this, [=]() {
        state = WEEKLY;
        loadCards();
    });
}

void SystemWindow::closeEvent(QCloseEvent *event) {
    HabitManager::save();
    qApp->quit();
}

void SystemWindow::initScrollArea() {
    QScrollArea *scrollArea = new QScrollArea(centralWidget());
    scrollArea->setWidgetResizable(true);
    scrollArea->setGeometry(80, 150, 450, 300);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setStyleSheet(
        "QScrollArea {"
        "   border: 1px solid #000000;"
        "   background-color: #FFFFFF;"
        "}"
    );

    scrollContainer = new QWidget(scrollArea);
    scrollContainer->setFixedHeight(scrollArea->height() - 20);
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

    PushButton *checkinButton = new PushButton("打卡", habitLabel);
    checkinButton->addStyle("QPushButton{ font: bold 15px; }");
    checkinButton->setGeometry(20, 210, 50, 25);
    connect(checkinButton, &QPushButton::clicked, this, [=]() {
        checkinDialog->show(habit);
    });

    PushButton *deleteButton = new PushButton("删除", habitLabel);
    deleteButton->addStyle("QPushButton{ font: bold 15px; }");
    deleteButton->setGeometry(80, 210, 50, 25);
    connect(deleteButton, &QPushButton::clicked, this, [=] {
        deleteDialog->show(habit);
    });

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
}
