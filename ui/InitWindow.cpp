//
// Created by xyx on 25-5-22.
//
#include "InitWindow.h"
#include <QApplication>
#include <QPushButton>
#include <QLabel>

InitWindow::InitWindow(QWidget *parent) : QMainWindow(parent) {
    initWindow();
    initButton();
    systemWindow = new SystemWindow(this);
}

InitWindow::~InitWindow() = default;

void InitWindow::initWindow() {
    setWindowTitle("习惯打卡管理系统");
    setFixedSize(400, 200);

    auto *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    centralWidget->setStyleSheet("background-color: #e3e3e3;");
    centralWidget->setFixedSize(this->width(), this->height());

    QLabel *title = new QLabel("习惯打卡管理系统", centralWidget);
    title->setStyleSheet(
        "QLabel {"
        "   font: bold 24px;"
        "   color: #000000;"
        "   background: transparent;"
        "}"
    );
    title->setGeometry(100, 20, 200, 40);
}

void InitWindow::initButton() {
    QPushButton *startButton = new QPushButton("进入系统", centralWidget());
    startButton->setStyleSheet(
        "QPushButton {"
        "   color: #000000;"
        "   background-color: #f9f4f4;"
        "   border: 1px solid #000000;"
        "   font: bold 20px;"
        "}"
        "QPushButton:hover { background-color: #b0aeae; }"
    );
    startButton->setGeometry(70, 100, 100, 50);
    InitWindow *initWindow = this;
    connect(startButton, &QPushButton::clicked, [=] {
        systemWindow->move(initWindow->pos());
        systemWindow->show();
        initWindow->hide();
    });

    QPushButton *exitButton = new QPushButton("关闭", centralWidget());
    exitButton->setStyleSheet(
        "QPushButton {"
        "   color: #000000;"
        "   background-color: #f9f4f4;"
        "   border: 1px solid #000000;"
        "   font: bold 20px;"
        "}"
        "QPushButton:hover { background-color: #b0aeae; }"
    );
    exitButton->setGeometry(220, 100, 100, 50);
    connect(exitButton, &QPushButton::clicked, this,  [=] {
        qApp->closeAllWindows();
    });
}

void InitWindow::closeEvent(QCloseEvent *event) {
    qApp->closeAllWindows();
}