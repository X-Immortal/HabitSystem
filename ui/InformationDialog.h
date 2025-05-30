//
// Created by  Apple on 25-5-29.
//

#ifndef INFOMATIONDIALOG_H
#define INFOMATIONDIALOG_H

#include "ScrolledDialog.h"
#include "../data/Habit.h"

class InformationDialog : public ScrolledDialog {
    Q_OBJECT

protected:
    Habit *habit;

public:
    InformationDialog(QWidget *parent = nullptr);
    void show(Habit *habit);
};

#endif //INFOMATIONDIALOG_H
