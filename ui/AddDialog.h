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
#include "../data/Habit.h"

class AddDialog : public QDialog {
    Q_OBJECT

    struct Name {
        QLineEdit *nameEdit;
        QLabel *prompt;

        bool check() const;
    } name;

    struct Description {
        QTextEdit *descriptionEdit;
        QLabel *prompt;

        bool check() const;
    } description;

    struct Target {
        QComboBox *typeBox;
        QLabel *prompt;

        bool check() const;
    } target;

    struct DailyTarget {
        QLabel *targetLabel;
        QSpinBox *targetEdit;
        QLabel *prompt;

        void hide() const;

        void show() const;

        [[nodiscard]] bool check() const;
    } dailyTarget;

    struct WeeklyTarget {
        QLabel *targetLabel;
        QSpinBox *targetEdit;
        QLabel *targetPrompt;
        QLabel *frequencyLabel;
        QSpinBox *frequencyEdit;
        QLabel *frequencyPrompt;

        void hide() const;

        void show() const;

        [[nodiscard]] bool check() const;
    } weeklyTarget;

public:
    explicit AddDialog(QWidget *parent);

signals:
    void habitAdded();

private:
    void initDialog();

    void initEdit();

    void initComboBox();

    void initSpinBox();

    void initButton();

    void addHabit();

    void clear();
};

#endif //ADDDIALOG_H
