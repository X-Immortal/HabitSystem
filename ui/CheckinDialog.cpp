//
// Created by  Apple on 25-5-29.
//

#include "CheckinDialog.h"
#include <QHBoxLayout>
#include "PushButton.h"
#include <QWidget>

CheckinDialog::CheckinDialog(QWidget *parent) : InformationDialog(parent) {
    setWindowTitle("打卡");

    QWidget *buttonContainer = new QWidget(scrollContainer);
    buttonContainer->setFixedWidth(scrollContainer->width());
    buttonContainer->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    buttonContainer->setStyleSheet("background: transparent;");
    scrollContainer->layout()->addWidget(buttonContainer);

    QHBoxLayout *buttonLayout = new QHBoxLayout(buttonContainer);
    buttonLayout->setAlignment(Qt::AlignCenter);
    buttonLayout->setSpacing(70);
    buttonContainer->setLayout(buttonLayout);

    PushButton *confirmButton = new PushButton("打卡", scrollContainer);
    confirmButton->setFixedSize(80, 50);
    confirmButton->addStyle("QPushButton { font-size: 20px; }");
    connect(confirmButton, &QPushButton::clicked, [this] {
        this->close();
        emit checkinConfirmed(habit);
    });
    buttonLayout->addWidget(confirmButton);

    PushButton *cancelButton = new PushButton("取消", scrollContainer);
    cancelButton->setFixedSize(80, 50);
    cancelButton->addStyle("QPushButton { font-size: 20px; }");
    connect(cancelButton, &QPushButton::clicked, [this] {
        this->close();
    });
    buttonLayout->addWidget(cancelButton);

    scrollContainer->layout()->addWidget(buttonContainer);
}
