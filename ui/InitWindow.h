//
// Created by xyx on 25-5-22.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "SystemWindow.h"

class InitWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit InitWindow(QWidget *parent = nullptr);

signals:
    void enterSystemRequested();

private:
    void initWindow();
    void initButton();
};

#endif //MAINWINDOW_H
