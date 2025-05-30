//
// Created by  Apple on 25-5-29.
//

#include "DeleteDialog.h"

#include <QHBoxLayout>

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
    QWidget *buttonContainer = new QWidget(this);
    buttonContainer->setGeometry(0, 60, width(), 25);
    buttonContainer->setStyleSheet("background: transparent;");

    QHBoxLayout *buttonLayout = new QHBoxLayout(buttonContainer);
    buttonLayout->setContentsMargins(20, 0, 20, 0);
    buttonLayout->setSpacing(0);
    buttonContainer->setLayout(buttonLayout);

    PushButton *confirmButton = new PushButton("确定", this);
    confirmButton->addStyle("QPushButton { font-size: 15px; }");
    confirmButton->setFixedSize(60, 25);
    connect(confirmButton, &QPushButton::clicked, this, [=] {
        this->close();
        emit deleteConfirmed(this->habit);
    });
    buttonLayout->addWidget(confirmButton);

    PushButton *cancelButton = new PushButton("取消", this);
    cancelButton->addStyle("QPushButton { font-size: 15px; }");
    cancelButton->setFixedSize(60, 25);
    connect(cancelButton, &QPushButton::clicked, this, [=] {
        this->close();
    });
    buttonLayout->addWidget(cancelButton);
}
