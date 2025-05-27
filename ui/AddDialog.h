//
// Created by  Apple on 25-5-26.
//

#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QLabel>
#include <QSpinBox>

class AddDialog : public QDialog {
    Q_OBJECT

    struct Name {
        QLineEdit *nameEdit;
        QLabel *prompt;

        bool check();
    } name;

    struct Description {
        QTextEdit *descriptionEdit;
        QLabel *prompt;

        bool check();
    } description;

    struct Target {
        QComboBox *typeBox;
        QLabel *prompt;

        bool check();
    } target;

    struct DailyTarget {
        QLabel *targetLabel;
        QSpinBox *targetEdit;

        void hide() const;

        void show() const;
    } dailyTarget;

    struct WeeklyTarget {
        QLabel *targetLabel;
        QSpinBox *targetEdit;
        QLabel *frequencyLabel;
        QSpinBox *frequencyEdit;

        void hide() const;

        void show() const;
    } weeklyTarget;

public:
    AddDialog(QWidget *parent);

private:
    void initDialog();

    void initEdit();

    void initComboBox();

    void initSpinBox();

    void initButton();

    void addHabit();
};

#endif //ADDDIALOG_H
