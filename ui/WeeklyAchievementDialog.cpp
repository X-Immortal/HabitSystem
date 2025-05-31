//
// Created by xyx on 25-5-30.
//

#include "WeeklyAchievementDialog.h"
#include "../data/HabitManager.h"

WeeklyAchievementDialog::WeeklyAchievementDialog(QWidget *parent) : ScrolledDialog(parent) {
    setWindowTitle("本周成就");
    try {
        infoLabel->setText(QString::fromStdString(HabitManager::updateWeek()));
    } catch (runtime_error &e) {
        if (strcmp(e.what(), "no new week") == 0) {
            throw;
        }
    }
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowModality(Qt::ApplicationModal);
}