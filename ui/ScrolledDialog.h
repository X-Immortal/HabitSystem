//
// Created by xyx on 25-5-30.
//

#ifndef SCROLLEDDIALOG_H
#define SCROLLEDDIALOG_H

#include <QDialog>
#include <QLabel>

class ScrolledDialog : public QDialog {
    Q_OBJECT

protected:
    QLabel *infoLabel;
    QWidget *scrollContainer;

    ScrolledDialog(QWidget *parent);
};

#endif //SCROLLEDDIALOG_H
