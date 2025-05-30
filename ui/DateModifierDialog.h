//
// Created by xyx on 25-5-30.
//

#ifndef DATEMODIFIERDIALOG_H
#define DATEMODIFIERDIALOG_H

#include <QDialog>
#include "../tools/Date.h"

class DateModifierDialog : public QDialog {
    Q_OBJECT

    Date date;

public:
    DateModifierDialog(QWidget *parent = nullptr);


};

#endif //DATEMODIFIERDIALOG_H
