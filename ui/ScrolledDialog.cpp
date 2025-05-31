//
// Created by xyx on 25-5-30.
//

#include "ScrolledDialog.h"
#include "../tools/Photo.h"
#include <QScrollArea>
#include <QVBoxLayout>

ScrolledDialog::ScrolledDialog(QWidget *parent) : QDialog(parent) {
    setFixedSize(300, 400);
    setStyleSheet("background-color: #e3e3e3;");

    if (Photo::hasDialogBackground()) {
        QLabel *photoLabel = new QLabel(this);
        QPixmap photo = Photo::getDialogBackground();
        photoLabel->setPixmap(photo);
        photoLabel->setFixedSize(photo.size());

        QWidget *widget = new QWidget(photoLabel);
        widget->setStyleSheet("background-color: rgba(255, 255, 255, 0.5);");
        widget->setFixedSize(photo.size());
    }

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFixedSize(this->width(), this->height());
    scrollArea->setStyleSheet("QScrollArea { background: transparent; }");
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    scrollContainer = new QWidget(scrollArea);
    scrollContainer->setFixedWidth(scrollArea->width() - 15);
    scrollContainer->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    scrollContainer->setStyleSheet("QWidget{background: transparent;}");
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
        "   background: transparent;"
        "}"
    );
    scrollLayout->addWidget(infoLabel);
}
