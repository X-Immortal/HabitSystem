//
// Created by xyx on 25-5-30.
//

#ifndef DATEMODIFIERDIALOG_H
#define DATEMODIFIERDIALOG_H

#include <QDateEdit>
#include <QDialog>
#include <QSlider>
#include "../tools/Date.h"

class DateModifierDialog : public QDialog {
    Q_OBJECT

    QSlider *switchSlider;
    QDateEdit *dateEdit;

public:
    DateModifierDialog(QWidget *parent = nullptr);

signals:
    void dateModified();

private:
    void initDialog();
    void initSlider();
    void initDateEdit();
    void initButton();
    void closeEvent(QCloseEvent *event) override;
};

#endif //DATEMODIFIERDIALOG_H
