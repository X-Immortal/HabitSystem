//
// Created by xyx on 25-5-22.
//

#ifndef SYSTEMWINDOW_H
#define SYSTEMWINDOW_H

#include <QMainWindow>

class SystemWindow : public QMainWindow {
    Q_OBJECT

protected:
    void closeEvent(QCloseEvent *event) override;

public:
    explicit SystemWindow(QWidget *parent = nullptr);
    ~SystemWindow();

private:
    void initWindow();
    void initButton();
};

#endif //SYSTEMWINDOW_H
