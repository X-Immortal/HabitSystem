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

    QLabel *infoLabel;
    Habit *habit;

public:
    InformationDialog(QWidget *parent = nullptr);
    void setHabit(Habit *habit);

private:
    void initDialog();
    void showInfo() const;
};

#endif //INFOMATIONDIALOG_H
