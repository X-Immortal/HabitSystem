//
// Created by xyx on 25-5-22.
//

#ifndef SYSTEMWINDOW_H
#define SYSTEMWINDOW_H

#include <QMainWindow>
#include "AddDialog.h"
#include "../data/Habit.h"

class SystemWindow : public QMainWindow {
    Q_OBJECT
    QWidget *scrollContainer;
    AddDialog *addDialog;

protected:
    void closeEvent(QCloseEvent *event) override;

public:
    explicit SystemWindow(QWidget *parent = nullptr);
    void loadCards(vector<Habit *> habits);

private:
    void initWindow();
    void initText();
    void initButton();
    void initScrollArea();
    void initDialog();
    void addCard(Habit *habit);
    void clearCards();
};

#endif //SYSTEMWINDOW_H
