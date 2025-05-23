//
// Created by xyx on 25-5-22.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "SystemWindow.h"

class InitWindow : public QMainWindow
{
    Q_OBJECT

protected:
    void closeEvent(QCloseEvent *event) override;

public:
    explicit InitWindow(QWidget *parent = nullptr);
    ~InitWindow();

private:
    SystemWindow *systemWindow;
    void initWindow();
    void initButton();
};

#endif //MAINWINDOW_H
