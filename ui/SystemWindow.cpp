//
// Created by xyx on 25-5-22.
//
#include "SystemWindow.h"
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QDate>
#include <QScrollArea>
#include <QSizePolicy>
#include <QHBoxLayout>
#include "../data/HabitManager.h"

SystemWindow::SystemWindow(QWidget *parent) : QMainWindow(parent) {
    initWindow();
    initText();
    initButton();
    initScrollArea();
    initDialog();
    loadCards(HabitManager::getHabits());
}

void SystemWindow::initWindow() {
    setWindowTitle("习惯打卡管理系统");
    setFixedSize(700, 500);

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
    QPushButton *allButton = new QPushButton("All", centralWidget());
    allButton->setStyleSheet(
        "QPushButton {"
        "   color: #000000;"
        "   background-color: #f9f4f4;"
        "   border: 1px solid #000000;"
        "   font: 30px Times-New-Roman;"
        "}"
        "QPushButton:hover { background-color: #b0aeae; }"
    );
    allButton->setGeometry(550, 170, 100, 50);
    connect(allButton, &QPushButton::clicked, this, [=]() {
        loadCards(HabitManager::getHabits());
    });

    QPushButton *dailyButton = new QPushButton("Daily", centralWidget());
    dailyButton->setStyleSheet(
        "QPushButton {"
        "   color: #000000;"
        "   background-color: #f9f4f4;"
        "   border: 1px solid #000000;"
        "   font: 30px Times-New-Roman;"
        "}"
        "QPushButton:hover { background-color: #b0aeae; }"
    );
    dailyButton->setGeometry(550, 270, 100, 50);
    connect(dailyButton, &QPushButton::clicked, this, [=]() {
        loadCards(HabitManager::getDailyHabits());
    });

    QPushButton *weeklyButton = new QPushButton("Weekly", centralWidget());
    weeklyButton->setStyleSheet(
        "QPushButton {"
        "   color: #000000;"
        "   background-color: #f9f4f4;"
        "   border: 1px solid #000000;"
        "   font: 30px Times-New-Roman;"
        "}"
        "QPushButton:hover { background-color: #b0aeae; }"
    );
    weeklyButton->setGeometry(550, 370, 100, 50);
    connect(weeklyButton, &QPushButton::clicked, this, [=]() {
        loadCards(HabitManager::getWeeklyHabits());
    });
}

void SystemWindow::closeEvent(QCloseEvent *event) {
    HabitManager::saveToFile();
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
}

void SystemWindow::addCard(Habit *habit) {
    QLabel *habitLabel = new QLabel(
        QString::fromStdString(habit->toSimpleString()),
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
    habitLabel->setLayout(nullptr);
    habitLabel->setWordWrap(true);
    scrollContainer->layout()->addWidget(habitLabel);

    QPushButton *checkinButton = new QPushButton("打卡", habitLabel);
    checkinButton->setStyleSheet(
        "QPushButton{"
        "   color: #000000;"
        "   background-color: #f9f4f4;"
        "   border: 1px solid #000000;"
        "   font: bold 15px;"
        "}"
        "QPushButton:hover { background-color: #b0aeae; }"
    );
    checkinButton->setGeometry(20, 210, 50, 25);
    connect(checkinButton, &QPushButton::clicked, this, [=]() {
        habit->checkin();
        habitLabel->setText(QString::fromStdString(habit->toSimpleString()));
    });

    QPushButton *deleteButton = new QPushButton("删除", habitLabel);
    deleteButton->setStyleSheet(
        "QPushButton{"
        "   color: #000000;"
        "   background-color: #f9f4f4;"
        "   border: 1px solid #000000;"
        "   font: bold 15px;"
        "}"
        "QPushButton:hover { background-color: #b0aeae; }"
    );
    deleteButton->setGeometry(80, 210, 50, 25);
    connect(deleteButton, &QPushButton::clicked, this, [=]() {
        HabitManager::del(habit->getName());
        habitLabel->deleteLater();
    });
}

void SystemWindow::clearCards() {
    QList<QWidget*> childWidgets = scrollContainer->findChildren<QWidget*>();
    for (QWidget *widget : childWidgets) {
        widget->deleteLater();
    }
}

void SystemWindow::loadCards(vector<Habit *> habits) {
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
}
