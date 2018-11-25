#include "UI/mainwindow.h"
#include "Communicator/communicator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Communicator * communicator = new Communicator();
    MainWindow * window = new MainWindow(communicator, 0);
    window->resize(800, 600);
    window->show();
    return a.exec();
}
