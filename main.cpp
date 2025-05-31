//
// Created by xyx on 25-5-22.
//
#include <QApplication>
#include "ui/InitWindow.h"
#include "ui/SystemWindow.h"
#include "tools/Photo.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Photo::loadPhotos();
    InitWindow *initWindow = new InitWindow();

    QObject::connect(initWindow, &InitWindow::enterSystemRequested, [=] {
        SystemWindow *systemWindow = new SystemWindow();
        systemWindow->show();
    });

    initWindow->show();
    return QApplication::exec();
}