#include "mainwindow.h"
#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow win;
    win.resize(600,500);
    win.setWindowIcon(QIcon("/home/xizhou/Qt/HelloWidget/src/le.ico"));
    win.show();

    return app.exec();
}

