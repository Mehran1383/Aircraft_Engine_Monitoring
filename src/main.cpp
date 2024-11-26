#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow m_MainWindow;
    m_MainWindow.show();
    return app.exec();
}



