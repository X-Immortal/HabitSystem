//
// Created by  Apple on 25-5-29.
//

#ifndef CHECKINDIALOG_H
#define CHECKINDIALOG_H

#include "InformationDialog.h"

class CheckinDialog : public InformationDialog {
    Q_OBJECT

public:
    CheckinDialog(QWidget *parent = nullptr);

private:
    void initDialog();
    void initButton();
};

#endif //CHECKINDIALOG_H
