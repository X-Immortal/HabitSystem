//
// Created by  Apple on 25-5-29.
//

#include "InformationDialog.h"
#include  <QScrollArea>
#include <QVBoxLayout>

InformationDialog::InformationDialog(QWidget *parent) : QDialog(parent){
    initDialog();
}

void InformationDialog::initDialog() {
    setWindowTitle("详细信息");
    setFixedSize(300, 400);
    setStyleSheet("background-color: #e3e3e3;");

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setFixedSize(this->width(), this->height());
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    QWidget *scrollContainer = new QWidget(scrollArea);
    scrollContainer->setFixedWidth(scrollArea->width());
    scrollContainer->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    scrollArea->setWidget(scrollContainer);

    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollContainer);
    scrollContainer->setLayout(scrollLayout);

    infoLabel = new QLabel(scrollArea);
    infoLabel->setWordWrap(true);
}

void InformationDialog::setHabit(Habit *habit) {
    this->habit = habit;
    showInfo();
}

void InformationDialog::showInfo() const {
    infoLabel->setText(QString::fromStdString(habit->toString()));
}

