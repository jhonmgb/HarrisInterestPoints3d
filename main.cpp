#include "UI/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow * window = new MainWindow(0);
    window->resize(800, 600);
    window->show();
    return a.exec();
}
