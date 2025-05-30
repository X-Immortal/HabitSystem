//
// Created by xyx on 25-5-30.
//

#include "ScrolledDialog.h"
#include <QScrollArea>
#include <QVBoxLayout>

ScrolledDialog::ScrolledDialog(QWidget *parent) : QDialog(parent) {
    setFixedSize(300, 400);
    setStyleSheet("background-color: #e3e3e3;");

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFixedSize(this->width(), this->height());
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    scrollContainer = new QWidget(scrollArea);
    scrollContainer->setFixedWidth(scrollArea->width() - 10);
    scrollContainer->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    scrollArea->setWidget(scrollContainer);

    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollContainer);
    scrollLayout->setSpacing(5);
    scrollContainer->setLayout(scrollLayout);

    infoLabel = new QLabel(scrollContainer);
    infoLabel->setWordWrap(true);
    infoLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    infoLabel->setStyleSheet(
        "QLabel {"
        "   font-size: 20px;"
        "   color: black;"
        "}"
    );
    scrollLayout->addWidget(infoLabel);
}
