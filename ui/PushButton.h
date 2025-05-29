//
// Created by xyx on 25-5-29.
//

#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <QPushButton>

class PushButton : public QPushButton {
    Q_OBJECT
    QString styleSheet;

public:
    PushButton(QWidget *parent = nullptr);

    PushButton(const QString &text, QWidget *parent = nullptr);

    void addStyle(const QString& styleSheet);

private:
    void initButton();
};

#endif //PUSHBUTTON_H
