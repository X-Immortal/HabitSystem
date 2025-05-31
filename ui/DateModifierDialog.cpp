//
// Created by xyx on 25-5-30.
//

#include "DateModifierDialog.h"
#include <QStyle>
#include <QCalendarWidget>
#include <QHBoxLayout>
#include "PushButton.h"

class SwitchSlider : public QSlider {
public:
    SwitchSlider(Qt::Orientation orientation, QWidget *parent) : QSlider(orientation, parent) {
        setRange(0, 1);
        setSingleStep(1);
        setValue(Date::canModify());
        setStyleSheet(
            "QSlider::groove:horizontal {"
            "   background: #d3d3d3;"
            "   height: 26px;"
            "   border-radius: 13px;"
            "}"
            "QSlider::handle:horizontal {"
            "   background: white;"
            "   width: 26px;"
            "   height: 26px;"
            "   border-radius: 13px;"
            "}"
            "QSlider[value='1']::groove:horizontal {"
            "   background: green;"
            "}"
        );
    }

    void mousePressEvent(QMouseEvent *event) override {
        setValue(1 - value());
    }

    void sliderChange(SliderChange change) override {
        QSlider::sliderChange(change);
        if (change == SliderValueChange) {
            style()->unpolish(this);
            style()->polish(this);
        }
    }
};

DateModifierDialog::DateModifierDialog(QWidget *parent) : QDialog(parent) {
    initDialog();
    initSlider();
    initDateEdit();
    initButton();
}

void DateModifierDialog::initDialog() {
    setWindowTitle("日期修改器");
    setFixedSize(320, 220);
    setStyleSheet("background-color: #e3e3e3;");
}

void DateModifierDialog::initSlider() {
    switchSlider = new SwitchSlider(Qt::Horizontal, this);
    switchSlider->setGeometry(10, 10, 60, 30);
}

void DateModifierDialog::initDateEdit() {
    dateEdit = new QDateEdit(Date::today(), this);
    dateEdit->setGeometry(80, 10, 220, 30);
    dateEdit->setCalendarPopup(true);
    dateEdit->setEnabled(Date::canModify());
    dateEdit->setStyleSheet(
        "QDateEdit {"
        "   color: black;"
        "   border: 1px solid black;"
        "   background-color: white;"
        "   font-size: 15px;"
        "}"
        "QDateEdit:disabled {"
        "   color: grey;"
        "   background-color: silver;"
        "}"
    );
    dateEdit->calendarWidget()->setStyleSheet(
        "QCalendarWidget QTableView::item {"
        "   color: black;"
        "}"
        "QCalendarWidget QTableView::item:selected {"
        "   background-color: orange;"
        "   color: red;"
        "}"
        "QCalendarWidget QTableView::item:hover {"
        "   background: grey;"
        "   border: 2px solid #81C784;"
        "   color: brown;"
        "}"
        "QCalendarWidget QToolButton:hover {"
        "   color: brown;"
        "   background: grey;"
        "   border: 2px solid #81C784;"
        "}"
    );
    connect(switchSlider, &QSlider::valueChanged, [this](int value) {
        switch (value) {
            case 0:
                dateEdit->setEnabled(false);
                dateEdit->setDate(QDate::currentDate());
                Date::setModifiable(false);
                break;
            case 1:
                dateEdit->setEnabled(true);
                Date::setModifiable(true);
                break;
            default:
                break;
        }
    });
}

void DateModifierDialog::initButton() {
    QWidget *buttonContainer = new QWidget(this);
    buttonContainer->setGeometry(0, 60, width(), 160);
    buttonContainer->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    buttonContainer->setStyleSheet("background: transparent;");

    QHBoxLayout *buttonLayout = new QHBoxLayout(buttonContainer);
    buttonContainer->setLayout(buttonLayout);

    PushButton *okButton = new PushButton("确定", this);
    okButton->setFixedSize(120, 120);
    okButton->addStyle("QPushButton { font-size: 20px; border-radius: 60px; }");
    connect(okButton, &QPushButton::clicked, [this] {
        switch (switchSlider->value()) {
            case 0:
                Date::setRealToday();
                break;
            case 1:
                Date::setToday(dateEdit->date());
                break;
            default:
                break;
        }
        emit dateModified();
        close();
    });
    buttonLayout->addWidget(okButton);
}

void DateModifierDialog::closeEvent(QCloseEvent *event) {
    switchSlider->setValue(Date::canModify());
    dateEdit->setDate(Date::today());
    close();
}
