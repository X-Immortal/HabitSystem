//
// Created by  Apple on 25-5-26.
//

#include "AddDialog.h"
#include <QPushButton>
#include "../data/HabitManager.h"

AddDialog::AddDialog(QWidget *parent) : QDialog(parent) {
    initDialog();
    initEdit();
    initSpinBox();
    initComboBox();
    initButton();
}

void AddDialog::DailyTarget::hide() const {
    assert(targetLabel && targetEdit);
    targetEdit->hide();
    targetLabel->hide();
}

void AddDialog::DailyTarget::show() const {
    assert(targetLabel && targetEdit);
    targetEdit->show();
    targetLabel->show();
}

void AddDialog::WeeklyTarget::hide() const {
    assert(targetLabel && targetEdit && frequencyEdit && frequencyLabel);
    targetEdit->hide();
    targetLabel->hide();
    frequencyEdit->hide();
    frequencyLabel->hide();
}

void AddDialog::WeeklyTarget::show() const {
    assert(targetLabel && targetEdit && frequencyEdit && frequencyLabel);
    targetEdit->show();
    targetLabel->show();
    frequencyEdit->show();
    frequencyLabel->show();
}

bool AddDialog::Name::check() {
    assert(nameEdit && prompt);
    if (nameEdit->text().isEmpty()) {
        prompt->show();
        return false;
    }
    prompt->hide();
    return true;
}

bool AddDialog::Description::check() {
    assert(descriptionEdit && prompt);
    if (descriptionEdit->toPlainText().isEmpty()) {
        prompt->show();
        return false;
    }
    prompt->hide();
    return true;
}

bool AddDialog::Target::check() {
    assert(typeBox && prompt);
    if (typeBox->currentIndex() == -1) {
        prompt->show();
        return false;
    }
    prompt->hide();
    return true;
}


void AddDialog::initDialog() {
    this->setWindowTitle("添加习惯");
    this->setFixedSize(400, 500);
    this->setLayout(nullptr);
}

void AddDialog::initEdit() {
    QLabel *nameLabel = new QLabel(this);
    nameLabel->setGeometry(20, 50, 100, 30);
    nameLabel->setText("名称");
    nameLabel->setStyleSheet(
        "QLabel {"
        "   font: 20px #000000;"
        "   background: transparent;"
        "}"
    );

    name.nameEdit = new QLineEdit(this);
    name.nameEdit->setGeometry(70, 50, 300, 30);
    name.nameEdit->setStyleSheet(
        "QLineEdit {"
        "   border: 1px solid #000000;"
        "   background-color: #FFFFFF;"
        "   font: 20px;"
        "}"
    );

    name.prompt = new QLabel("请输入习惯名称!", this);
    name.prompt->setGeometry(80, 85, 100, 10);
    name.prompt->setStyleSheet(
        "QLabel {"
        "   font: 10px;"
        "   color: #FF0000;"
        "   background: transparent;"
        "}"
    );


    QLabel *descriptionLabel = new QLabel(this);
    descriptionLabel->setGeometry(20, 100, 100, 30);
    descriptionLabel->setText("描述");
    descriptionLabel->setStyleSheet(
        "QLabel {"
        "   font: 20px #000000;"
        "   background: transparent;"
        "}"
    );

    description.descriptionEdit = new QTextEdit(this);
    description.descriptionEdit->setGeometry(70, 100, 300, 200);
    description.descriptionEdit->setStyleSheet(
        "QTextEdit {"
        "   border: 1px solid #000000;"
        "   background-color: #FFFFFF;"
        "   font: 20px;"
        "}"
    );

    description.prompt = new QLabel("请输入习惯描述！", this);
    description.prompt->setGeometry(80, 305, 100, 10);
    description.prompt->setStyleSheet(
        "QLabel {"
        "   color: #FF0000;"
        "   font: 10px;"
        "   background-color: transparent;"
        "}"
    );
}

void AddDialog::initSpinBox() {
    dailyTarget.targetLabel = new QLabel(this);
    dailyTarget.targetLabel->setGeometry(50, 370, 100, 30);
    dailyTarget.targetLabel->setText("目标天数");
    dailyTarget.targetLabel->setStyleSheet(
        "QLabel {"
        "   font: 20px #000000;"
        "   background: transparent;"
        "}"
    );

    dailyTarget.targetEdit = new QSpinBox(this);
    dailyTarget.targetEdit->setGeometry(150, 370, 70, 30);
    dailyTarget.targetEdit->setStyleSheet(
        "QSpinBox {"
        "   font: 20px #000000;"
        "}"
    );

    dailyTarget.hide();

    weeklyTarget.targetLabel = new QLabel(this);
    weeklyTarget.targetLabel->setGeometry(50, 370, 100, 30);
    weeklyTarget.targetLabel->setText("目标周数");
    weeklyTarget.targetLabel->setStyleSheet(
        "QLabel {"
        "   font: 20px #000000;"
        "   background: transparent;"
        "}"
    );

    weeklyTarget.targetEdit = new QSpinBox(this);
    weeklyTarget.targetEdit->setGeometry(150, 370, 70, 30);
    weeklyTarget.targetEdit->setStyleSheet(
        "QSpinBox {"
        "   font: 20px #000000;"
        "}"
    );

    weeklyTarget.frequencyLabel = new QLabel(this);
    weeklyTarget.frequencyLabel->setGeometry(50, 420, 120, 30);
    weeklyTarget.frequencyLabel->setText("每周打卡次数");
    weeklyTarget.frequencyLabel->setStyleSheet(
        "QLabel {"
        "   font: 20px #000000;"
        "   background: transparent;"
        "}"
    );

    weeklyTarget.frequencyEdit = new QSpinBox(this);
    weeklyTarget.frequencyEdit->setGeometry(200, 420, 70, 30);
    weeklyTarget.frequencyEdit->setStyleSheet(
        "QSpinBox {"
        "   font: 20px #000000;"
        "}"
    );

    weeklyTarget.hide();
}


void AddDialog::initComboBox() {
    target.typeBox = new QComboBox(this);
    target.typeBox->setGeometry(70, 320, 300, 30);
    target.typeBox->setPlaceholderText("习惯类型");
    target.typeBox->addItems({ "每日习惯", "每周习惯"});
    target.typeBox->setStyleSheet(
        "QComboBox{"
        "   border: 1px solid #000000;"
        "   padding: 5px 10px;"
        "   font: 20px;"
        "}"
        "QComboBox::drop-down { width: 20px; }"
    );

    target.prompt = new QLabel("请选择习惯类型！", this);
    target.prompt->setGeometry(80, 355, 100, 10);
    target.prompt->setStyleSheet(
        "QLabel {"
        "   color: #FF0000;"
        "   font: 10px;"
        "   background-color: transparent;"
        "}"
    );

    connect(target.typeBox, &QComboBox::currentIndexChanged, [=](int index) {
        if (index == 0) {
            weeklyTarget.hide();
            dailyTarget.show();
        } else {
            dailyTarget.hide();
            weeklyTarget.show();
        }
    });
}

void AddDialog::initButton() {
    QPushButton *confirmButton = new QPushButton("确定", this);
    confirmButton->setGeometry(200, 470, 80, 20);
    confirmButton->setStyleSheet(
        "QPushButton {"
        "   color: #000000;"
        "   background-color: #f9f4f4;"
        "   border: 1px solid #000000;"
        "   font: 20px;"
        "}"
        "QPushButton:hover { background-color: #b0aeae; }"
    );

    QPushButton *cancelButton = new QPushButton("取消", this);
    cancelButton->setGeometry(300, 470, 80, 20);
    cancelButton->setStyleSheet(
        "QPushButton {"
        "   color: #000000;"
        "   background-color: #f9f4f4;"
        "   border: 1px solid #000000;"
        "   font: 20px;"
        "}"
        "QPushButton:hover { background-color: #b0aeae; }"
    );
    connect(cancelButton, &QPushButton::clicked, this, &AddDialog::close);
}

void AddDialog::addHabit() {
    if (name.nameEdit->text().isEmpty()) {

    }

    string name = this->name.nameEdit->text().toStdString();
    string description = this->description.descriptionEdit->toPlainText().toStdString();

}
