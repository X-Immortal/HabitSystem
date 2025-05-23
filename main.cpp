//
// Created by xyx on 25-5-22.
//
#include <QApplication>
#include "ui/InitWindow.h"
#include "ui/SystemWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    // InitWindow window;
    SystemWindow window;
    window.show();
    return QApplication::exec();
}