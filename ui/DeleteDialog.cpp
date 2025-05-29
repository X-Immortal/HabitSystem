//
// Created by  Apple on 25-5-29.
//

#include "DeleteDialog.h"
#include <QLabel>
#include <QPushButton>

DeleteDialog::DeleteDialog(QWidget *parent) : QDialog(parent) {
    initDialog();
    initButton();
}

void DeleteDialog::setHabit(Habit *habit) {
    this->habit = habit;
}

void DeleteDialog::initDialog() {
    setWindowTitle("提示");
    setFixedSize(250, 100);
    setStyleSheet("background-color: #e3e3e3;");

    QLabel *prompt = new QLabel("确定要删除该习惯吗？", this);
    prompt->setGeometry(30, 30, 200, 25);
    prompt->setStyleSheet("font-size: 20px;");
}

void DeleteDialog::initButton() {
    QPushButton *confirmButton = new QPushButton("确定", this);
    confirmButton->setGeometry(50, 70, 50, 20);
    connect(confirmButton, &QPushButton::clicked, this, [=] {
        this->close();
        emit deleteConfirmed(this->habit);
    });

    QPushButton *cancelButton = new QPushButton("取消", this);
    cancelButton->setGeometry(150, 70, 50, 20);
    connect(cancelButton, &QPushButton::clicked, this, [=] {
        this->close();
    });
}
