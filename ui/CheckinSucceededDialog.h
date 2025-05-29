//
// Created by xyx on 25-5-29.
//

#ifndef CHECKINSUCCEEDEDDIALOG_H
#define CHECKINSUCCEEDEDDIALOG_H

#include <QDialog>
#include <QLabel>

class CheckinSucceededDialog : public QDialog {
    Q_OBJECT

    bool isFinished = false;
    QLabel *prompt;

public:
    CheckinSucceededDialog(QWidget *parent = nullptr);

    void show(bool isFinished);
};

#endif //CHECKINSUCCEEDEDDIALOG_H
