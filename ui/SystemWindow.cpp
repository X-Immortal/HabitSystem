//
// Created by xyx on 25-5-22.
//
#include "SystemWindow.h"

#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>

SystemWindow::SystemWindow(QWidget *parent) : QMainWindow(parent) {
    initWindow();
    initButton();
}

SystemWindow::~SystemWindow() = default;

void SystemWindow::initWindow() {
    setWindowTitle("习惯打卡管理系统");
    setFixedSize(500, 500);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    centralWidget->setFixedSize(this->width(), this->height());
    centralWidget->setStyleSheet("background-color: #e3e3e3;");

    QLabel *title = new QLabel("TODO", centralWidget);
    title->setStyleSheet(
        "QLabel {"
        "   font: bold 40px;"
        "   color: #000000;"
        "   background: transparent;"
        "}"
    );
    title->setGeometry(190, 50, 200, 200);
}

void SystemWindow::initButton() {
    QPushButton *startButton = new QPushButton("打卡", centralWidget());
    startButton->setStyleSheet(
        "QPushButton {"
        "   color: #000000;"
        "   background-color: #f9f4f4;"
        "   border: 1px solid #000000;"
        "   font: bold 40px;"
        "}"
        "QPushButton:hover { background-color: #b0aeae; }"
    );
    startButton->setGeometry(200, 300, 100, 50);
}

void SystemWindow::closeEvent(QCloseEvent *event) {
    qApp->quit();
}
