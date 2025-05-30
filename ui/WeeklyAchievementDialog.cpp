//
// Created by xyx on 25-5-30.
//

#include "WeeklyAchievementDialog.h"
#include "../data/HabitManager.h"

WeeklyAchievementDialog::WeeklyAchievementDialog(QWidget *parent) : ScrolledDialog(parent) {
    infoLabel->setText(QString::fromStdString(HabitManager::updateWeek()));
    setAttribute(Qt::WA_DeleteOnClose);
}