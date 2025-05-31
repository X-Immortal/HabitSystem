//
// Created by xyx on 25-5-29.
//

#include "CheckinSucceededDialog.h"
#include <QLabel>
#include "PushButton.h"

CheckinSucceededDialog::CheckinSucceededDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("提示");
    setFixedSize(250, 100);
    setStyleSheet("background-color: #e3e3e3;");

    prompt = new QLabel(this);
    prompt->setGeometry(30, 10, 200, 50);
    prompt->setStyleSheet(
        "QLabel {"
        "   font-size: 20px;"
        "   color: black;"
        "}"
    );

    PushButton *okButton = new PushButton("确定", this);
    okButton->addStyle("QPushButton { font-size: 15px; }");
    okButton->setGeometry(90, 60, 60, 25);
    connect(okButton, &QPushButton::clicked, [this] {
        this->close();
    });
}

void CheckinSucceededDialog::show(bool isFinished) {
    if (isFinished) {
        prompt->setText("恭喜！该习惯已完成！");
    } else {
        prompt->setText("打卡成功，再接再厉！");
    }
    QDialog::show();
}

