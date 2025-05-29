//
// Created by  Apple on 25-5-29.
//

#ifndef INFOMATIONDIALOG_H
#define INFOMATIONDIALOG_H

#include <QDialog>
#include <QLabel>

#include "../data/Habit.h"

class InformationDialog : public QDialog {
    Q_OBJECT

protected:
    QLabel *infoLabel;
    Habit *habit;
    QWidget *scrollContainer;

public:
    InformationDialog(QWidget *parent = nullptr);
    void show(Habit *habit);
};

#endif //INFOMATIONDIALOG_H
