//
// Created by  Apple on 25-5-29.
//

#include "DeleteDialog.h"
#include "PushButton.h"
#include <QLabel>
#include <QPushButton>

DeleteDialog::DeleteDialog(QWidget *parent) : QDialog(parent) {
    initDialog();
    initButton();
}

void DeleteDialog::show(Habit *habit) {
    this->habit = habit;
    QDialog::show();
}

void DeleteDialog::initDialog() {
    setWindowTitle("提示");
    setFixedSize(250, 100);
    setStyleSheet("background-color: #e3e3e3;");

    QLabel *prompt = new QLabel("确定要删除该习惯吗？", this);
    prompt->setGeometry(30, 10, 200, 50);
    prompt->setStyleSheet(
        "QLabel {"
        "   font-size: 20px;"
        "   color: black;"
        "}"
    );
}

void DeleteDialog::initButton() {
    PushButton *confirmButton = new PushButton("确定", this);
    confirmButton->addStyle("QPushButton { font-size: 15px; }");
    confirmButton->setGeometry(45, 60, 60, 25);
    connect(confirmButton, &QPushButton::clicked, this, [=] {
        this->close();
        emit deleteConfirmed(this->habit);
    });

    PushButton *cancelButton = new PushButton("取消", this);
    cancelButton->addStyle("QPushButton { font-size: 15px; }");
    cancelButton->setGeometry(150, 60, 60, 25);
    connect(cancelButton, &QPushButton::clicked, this, [=] {
        this->close();
    });
}
