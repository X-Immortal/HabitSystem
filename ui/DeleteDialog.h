//
// Created by  Apple on 25-5-29.
//

#ifndef DELETEDIALOG_H
#define DELETEDIALOG_H

#include <QDialog>
#include "../data/Habit.h"

class DeleteDialog : public QDialog {
    Q_OBJECT

    Habit *habit;

public:
    explicit DeleteDialog(QWidget *parent = nullptr);

    void show(Habit *habit);

signals:
    void deleteConfirmed(Habit *habit);

private:
    void initDialog();
    void initButton();
};

#endif //DELETEDIALOG_H
