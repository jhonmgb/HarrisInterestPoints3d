#include "UI/mainwindow.h"
#include "Communicator/communicator.h"
#include "Engine/engine.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);

    QSurfaceFormat::setDefaultFormat(format);

    Engine * engine = new Engine();
    Communicator * communicator = new Communicator();
    communicator->bindEngine(engine);
    MainWindow * window = new MainWindow(communicator, 0);
    window->resize(800, 600);
    window->show();
    return a.exec();
}
