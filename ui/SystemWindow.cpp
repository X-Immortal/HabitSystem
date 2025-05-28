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
    loadCards();
}

SystemWindow::~SystemWindow() = default;

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
    title->setGeometry(190, 50, 310, 50);

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

void SystemWindow::loadCards() {
    for (int i = 0; i < 5; ++i) {
        QLabel *habit = new QLabel("习惯" + QString::number(i + 1), scrollContainer);
        habit->setStyleSheet(
            "QLabel {"
            "   font: 20px;"
            "   color: #000000;"
            "   background: #1e2ffc;"
            "   border: 1px solid #000000;"
            "}"
        );
        habit->setFixedSize(150, 200);
        habit->setLayout(nullptr);
        scrollContainer->layout()->addWidget(habit);

        QPushButton *checkinButton = new QPushButton("打卡", habit);
        checkinButton->setStyleSheet(
            "QPushButton{"
            "   color: #000000;"
            "   background-color: #f9f4f4;"
            "   border: 1px solid #000000;"
            "   font: bold 15px;"
            "}"
            "QPushButton:hover { background-color: #b0aeae; }"
        );
        checkinButton->setGeometry(20, 160, 50, 25);

        QPushButton *deleteButton = new QPushButton("删除", habit);
        deleteButton->setStyleSheet(
            "QPushButton{"
            "   color: #000000;"
            "   background-color: #f9f4f4;"
            "   border: 1px solid #000000;"
            "   font: bold 15px;"
            "}"
            "QPushButton:hover { background-color: #b0aeae; }"
        );
        deleteButton->setGeometry(80, 160, 50, 25);
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
    connect(addButton, &QPushButton::clicked, [=] {
        addDialog->show();
    });
    scrollContainer->layout()->addWidget(addButton);
}

void SystemWindow::initDialog() {
    addDialog = new AddDialog(this);
}
