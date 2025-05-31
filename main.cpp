//
// Created by xyx on 25-5-22.
//
#include <QApplication>
#include <QStyleFactory>
#include "ui/InitWindow.h"
#include "ui/SystemWindow.h"
#include "tools/Photo.h"
#include "ui/AddDialog.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Photo::loadPhotos();

    if (Photo::hasWindowIcon()) {
        QApplication::setWindowIcon(Photo::getWindowIcon());
    }

    InitWindow *initWindow = new InitWindow();

    QObject::connect(initWindow, &InitWindow::enterSystemRequested, [=] {
        SystemWindow *systemWindow = new SystemWindow();
        systemWindow->show();
    });

    initWindow->show();
    return QApplication::exec();
}
