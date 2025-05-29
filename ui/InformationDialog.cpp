//
// Created by  Apple on 25-5-29.
//

#include "InformationDialog.h"
#include <QScrollArea>
#include <QVBoxLayout>

InformationDialog::InformationDialog(QWidget *parent) : QDialog(parent){
    setWindowTitle("详细信息");
    setFixedSize(300, 400);
    setStyleSheet("background-color: #e3e3e3;");

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFixedSize(this->width(), this->height());
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    scrollContainer = new QWidget(scrollArea);
    scrollContainer->setFixedWidth(scrollArea->width() - 10);
    scrollContainer->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    scrollArea->setWidget(scrollContainer);

    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollContainer);
    scrollLayout->setSpacing(5);
    scrollContainer->setLayout(scrollLayout);

    infoLabel = new QLabel(scrollContainer);
    infoLabel->setWordWrap(true);
    infoLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    infoLabel->setStyleSheet(
        "QLabel {"
        "   font-size: 20px;"
        "   color: black;"
        "}"
    );
    scrollLayout->addWidget(infoLabel);
}

void InformationDialog::show(Habit *habit) {
    this->habit = habit;
    infoLabel->setText(habit->toString());
    QDialog::show();
}
