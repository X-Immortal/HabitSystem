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

public:
    enum State {ALL, DAILY, WEEKLY};

private:
    QWidget *scrollContainer;
    AddDialog *addDialog;
    DeleteDialog *deleteDialog;
    InformationDialog *informationDialog;
    CheckinDialog *checkinDialog;
    CheckinSucceededDialog *checkinSucceededDialog;
    DateModifierDialog *dateModifierDialog;
    State state = ALL;

protected:
    void closeEvent(QCloseEvent *event) override;

public:
    explicit SystemWindow(QWidget *parent = nullptr);
    void loadCards();

signals:
    void showAddDialogRequested(State state);

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
