//
// Created by xyx on 25-5-22.
//
#include "InitWindow.h"
#include <QApplication>
#include "PushButton.h"
#include <QLabel>

InitWindow::InitWindow(QWidget *parent) : QMainWindow(parent) {
    initWindow();
    initButton();
}

void InitWindow::initWindow() {
    setWindowTitle("习惯打卡管理系统");
    setFixedSize(400, 200);
    setAttribute(Qt::WA_DeleteOnClose);

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
    PushButton *startButton = new PushButton("进入系统", centralWidget());
    startButton->setGeometry(70, 100, 100, 50);
    startButton->addStyle("QPushButton { font-size: 20px; }");
    connect(startButton, &PushButton::clicked, [this] {
        emit enterSystemRequested();
        this->close();
    });

    PushButton *exitButton = new PushButton("关闭", centralWidget());
    exitButton->setGeometry(220, 100, 100, 50);
    exitButton->addStyle("QPushButton { font-size: 20px; }");
    connect(exitButton, &QPushButton::clicked, [this] {
        this->close();
    });
}