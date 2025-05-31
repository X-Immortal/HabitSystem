//
// Created by xyx on 25-5-22.
//

#ifndef SYSTEMWINDOW_H
#define SYSTEMWINDOW_H

#include <QMainWindow>
#include "AddDialog.h"
#include "DeleteDialog.h"
#include "InformationDialog.h"
#include "CheckinDialog.h"
#include "CheckinSucceededDialog.h"
#include "DateModifierDialog.h"
#include "../data/Habit.h"

class SystemWindow : public QMainWindow {
    Q_OBJECT

    QWidget *scrollContainer;
    AddDialog *addDialog;
    DeleteDialog *deleteDialog;
    InformationDialog *informationDialog;
    CheckinDialog *checkinDialog;
    CheckinSucceededDialog *checkinSucceededDialog;
    DateModifierDialog *dateModifierDialog;
    enum State {ALL, DAILY, WEEKLY} state = ALL;

protected:
    void closeEvent(QCloseEvent *event) override;

public:
    explicit SystemWindow(QWidget *parent = nullptr);
    void loadCards();

private:
    void initWindow();
    void initText();
    void initButton();
    void initScrollArea();
    void initDialog();
    void addCard(Habit *habit);
    void clearCards();
    void updateWeek();
};

#endif //SYSTEMWINDOW_H
