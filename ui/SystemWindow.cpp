//
// Created by xyx on 25-5-22.
//
#include "SystemWindow.h"

#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include "PushButton.h"
#include <QScrollArea>
#include <QSizePolicy>
#include <QHBoxLayout>
#include "../data/HabitManager.h"
#include "CheckinSucceededDialog.h"
#include "AddDialog.h"
#include "DeleteDialog.h"
#include "WeeklyAchievementDialog.h"
#include "../tools/Photo.h"

SystemWindow::SystemWindow(QWidget *parent) : QMainWindow(parent) {
    initWindow();
    initDialog();
    initText();
    initButton();
    initScrollArea();
    loadCards();
}

void SystemWindow::initWindow() {
    setWindowTitle("习惯打卡管理系统");
    setFixedSize(700, 500);
    setAttribute(Qt::WA_DeleteOnClose);

    QWidget *parent;
    if (Photo::hasBackground()) {
        QLabel *background = new QLabel(this);
        QPixmap backgroundMap = Photo::getBackground();
        background->setPixmap(backgroundMap);
        background->setFixedSize(backgroundMap.size());
        parent = background;
    } else {
        QWidget *backgroundWidget = new QWidget(this);
        backgroundWidget->setFixedSize(this->width(), this->height());
        backgroundWidget->setStyleSheet("background: grey;");
        parent = backgroundWidget;
    }
    setCentralWidget(parent);

    QWidget *centralWidget = new QWidget(parent);
    centralWidget->setFixedSize(this->width(), this->height());
    centralWidget->setStyleSheet("background-color: rgba(255, 255, 255, 0.4);");
}

void SystemWindow::initText() {
    QWidget *textContainer = new QWidget(this);
    textContainer->setGeometry(0, 45, width(), 90);
    textContainer->setStyleSheet("background: transparent;");

    QVBoxLayout *textLayout = new QVBoxLayout(textContainer);
    textLayout->setSpacing(10);
    textLayout->setContentsMargins(0, 0, 0, 0);
    textContainer->setLayout(textLayout);

    QLabel *title = new QLabel("习惯打卡管理系统", centralWidget());
    title->setStyleSheet("QLabel { font: bold 40px; color: black; background: transparent; }");
    title->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    title->setAlignment(Qt::AlignCenter);
    textLayout->addWidget(title);

    QPushButton *nowtime = new QPushButton("今天是" + QString::fromStdString(Date::today().toString()), centralWidget());
    nowtime->setStyleSheet("QPushButton { font: 20px; color: black; background: transparent; border: 0px; } QPushButton:hover { background: transparent; }");
    nowtime->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(nowtime, &QPushButton::clicked, [this] {
        HabitManager::save();
        dateModifierDialog->show();
    });
    connect(dateModifierDialog, &DateModifierDialog::dateModified, [this, nowtime] {
        nowtime->setText("今天是" + QString::fromStdString(Date::today().toString()));
    });
    textLayout->addWidget(nowtime);
    if (!HabitManager::isOnTest()) {
        nowtime->setEnabled(false);
    }
}


void SystemWindow::initButton() {
    QWidget *buttonContainer = new QWidget(this);
    buttonContainer->setGeometry(580, 150, 80, 300);
    buttonContainer->setStyleSheet("background: transparent;");

    QVBoxLayout *buttonLayout = new QVBoxLayout(buttonContainer);
    buttonLayout->setSpacing(20);
    buttonLayout->setContentsMargins(0, 0, 0, 0);
    buttonContainer->setLayout(buttonLayout);

    QString styleSheet = "QPushButton { font-size: 20px; font: Times-New-Roman; border-radius: 40px; }";

    PushButton *allButton = new PushButton("All", centralWidget());
    allButton->addStyle(styleSheet);
    allButton->setFixedSize(80, 80);
    connect(allButton, &QPushButton::clicked, [this]() {
        state = ALL;
        loadCards();
    });
    buttonLayout->addWidget(allButton);

    PushButton *dailyButton = new PushButton("Daily", centralWidget());
    dailyButton->addStyle(styleSheet);
    dailyButton->setFixedSize(80, 80);
    connect(dailyButton, &QPushButton::clicked, [this]() {
        state = DAILY;
        loadCards();
    });
    buttonLayout->addWidget(dailyButton);

    PushButton *weeklyButton = new PushButton("Weekly", centralWidget());
    weeklyButton->addStyle(styleSheet);
    weeklyButton->setFixedSize(80, 80);
    connect(weeklyButton, &QPushButton::clicked, [this]() {
        state = WEEKLY;
        loadCards();
    });
    buttonLayout->addWidget(weeklyButton);
}

void SystemWindow::closeEvent(QCloseEvent *event) {
    HabitManager::save();
    qApp->quit();
}

void SystemWindow::initScrollArea() {
    QScrollArea *scrollArea = new QScrollArea(centralWidget());
    scrollArea->setWidgetResizable(true);
    scrollArea->setGeometry(80, 150, 490, 300);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setStyleSheet("QScrollArea { border: 1px solid black; background: transparent; }");

    scrollContainer = new QWidget(scrollArea);
    scrollContainer->setFixedHeight(scrollArea->height() - 15);
    scrollContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    scrollContainer->setStyleSheet("QWidget { background-color: transparent; }");
    scrollArea->setWidget(scrollContainer);

    QHBoxLayout *scrollLayout = new QHBoxLayout(scrollContainer);
    scrollLayout->setSpacing(45);
    scrollContainer->setLayout(scrollLayout);

    connect(addDialog, &AddDialog::habitAdded, [this] {
        loadCards();
    });
}

void SystemWindow::addCard(Habit *habit) {
    QWidget *parent;
    if (Photo::hasPhoto()) {
        QLabel *photoLabel = new QLabel(scrollContainer);
        parent = photoLabel;
        QPixmap photo = Photo::getRandomPhoto();
        photoLabel->setPixmap(photo);
        photoLabel->setFixedSize(photo.size());
        scrollContainer->layout()->addWidget(photoLabel);
        QHBoxLayout *photoLayout = new QHBoxLayout(photoLabel);
        photoLayout->setContentsMargins(0, 0, 0, 0);
        photoLabel->setLayout(photoLayout);
    } else {
        QLabel *container = new QLabel(scrollContainer);
        container->setFixedSize(190, 266);
        parent = container;
        QHBoxLayout *containerLayout = new QHBoxLayout(container);
        containerLayout->setContentsMargins(0, 0, 0, 0);
        scrollContainer->layout()->addWidget(container);
    }
    QLabel *habitLabel = new QLabel(habit->toSimpleString(), parent);
    habitLabel->setStyleSheet(
        "QLabel {"
        "   font: 20px;"
        "   color: #000000;"
        "   background-color: rgba(255, 255, 255, 0.6);"
        "   border: 1px solid #000000;"
        "}"
    );
    habitLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    habitLabel->setWordWrap(true);
    parent->layout()->addWidget(habitLabel);

    QWidget *buttonContainer = new QWidget(parent);
    buttonContainer->setStyleSheet("background: transparent;");
    buttonContainer->setGeometry(0, 210, parent->width(), 35);

    QHBoxLayout *buttonLayout = new QHBoxLayout(buttonContainer);
    buttonLayout->setContentsMargins(0, 0, 0, 0);
    buttonContainer->setLayout(buttonLayout);

    if (habit->canCheckin()) {
        PushButton *checkinButton = new PushButton("打卡", habitLabel);
        checkinButton->addStyle("QPushButton{ font: bold 18px; }");
        checkinButton->setFixedSize(60, 30);
        connect(checkinButton, &QPushButton::clicked, [this, habit] {
            checkinDialog->show(habit);
        });
        buttonLayout->addWidget(checkinButton);
    }


    PushButton *deleteButton = new PushButton("删除", habitLabel);
    deleteButton->addStyle("QPushButton{ font: bold 18px; }");
    deleteButton->setFixedSize(60, 30);
    connect(deleteButton, &QPushButton::clicked, [this, habit] {
        deleteDialog->show(habit);
    });
    buttonLayout->addWidget(deleteButton);

    PushButton *infoButton = new PushButton("详情", parent);
    infoButton->addStyle("QPushButton{ font: bold; font-size: 15px; }");
    infoButton->setGeometry(120, 20, 50, 20);
    connect(infoButton, &QPushButton::clicked, [this, habit]() {
        informationDialog->show(habit);
    });
}

void SystemWindow::clearCards() {
    QList<QWidget *> childWidgets = scrollContainer->findChildren<QWidget *>();
    for (QWidget *widget: childWidgets) {
        widget->deleteLater();
    }
}

void SystemWindow::loadCards() {
    vector<Habit *> habits;
    switch (state) {
        case ALL:
            habits = HabitManager::getHabits();
            break;
        case DAILY:
            habits = HabitManager::getDailyHabits();
            break;
        case WEEKLY:
            habits = HabitManager::getWeeklyHabits();
            break;
        default:
            break;
    }

    clearCards();

    for (int i = 0; i < habits.size(); ++i) {
        addCard(habits[i]);
    }

    QPushButton *addButton = new QPushButton("+", scrollContainer);
    addButton->setFixedSize(190, 266);
    addButton->setStyleSheet(
        "QPushButton {"
        "   font: 90px;"
        "   color: orange;"
        "   background: rgba(255, 192, 203, 0.7);"
        "   border: 1px solid #000000;"
        "   padding: 0px;"
        "   text-align: center;"
        "}"
    );
    connect(addButton, &QPushButton::clicked, [this] {
        emit showAddDialogRequested(state);
    });
    scrollContainer->layout()->addWidget(addButton);
}

void SystemWindow::initDialog() {
    addDialog = new AddDialog(this);
    deleteDialog = new DeleteDialog(this);
    informationDialog = new InformationDialog(this);
    checkinDialog = new CheckinDialog(this);
    checkinSucceededDialog = new CheckinSucceededDialog(this);
    if (HabitManager::isOnTest()) {
        dateModifierDialog = new DateModifierDialog(this);
        connect(dateModifierDialog, &DateModifierDialog::dateModified, [this] {
            if (!Date::canModify()) {
                HabitManager::readHabits();
            }
            updateWeek();
            loadCards();
        });
    } else {
        dateModifierDialog = nullptr;
    }
    connect(checkinDialog, &CheckinDialog::checkinConfirmed, [this](Habit *habit) {
        habit->checkin();
        loadCards();
        checkinSucceededDialog->show(habit->isCompleted());
    });
    connect(deleteDialog, &DeleteDialog::deleteConfirmed, [this](Habit *habit) {
        HabitManager::del(habit->getName());
        loadCards();
    });
    updateWeek();
}

void SystemWindow::updateWeek() {
    try {
        WeeklyAchievementDialog *weeklyAchievementDialog = new WeeklyAchievementDialog(this);
        weeklyAchievementDialog->show();
    } catch ([[maybe_unused]] runtime_error &e) {
        if (strcmp(e.what(), "no new week") != 0) {
            throw;
        }
    }
}
