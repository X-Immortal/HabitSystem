//
// Created by  Apple on 25-5-29.
//

#include "InformationDialog.h"
#include <QScrollArea>
#include <QVBoxLayout>

InformationDialog::InformationDialog(QWidget *parent) : ScrolledDialog(parent){
    setWindowTitle("详细信息");
}

void InformationDialog::show(Habit *habit) {
    this->habit = habit;
    infoLabel->setText(habit->toString());
    QDialog::show();
}
