//
// Created by  Apple on 25-5-29.
//

#ifndef CHECKINDIALOG_H
#define CHECKINDIALOG_H

#include "InformationDialog.h"

class CheckinDialog : public InformationDialog {
    Q_OBJECT

public:
    explicit CheckinDialog(QWidget *parent = nullptr);

signals:
    void checkinConfirmed(Habit *habit);
};

#endif //CHECKINDIALOG_H
