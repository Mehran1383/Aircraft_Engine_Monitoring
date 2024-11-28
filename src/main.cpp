#include "mainwindow.h"
#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QPalette palette;

    // Load an application style
    QFile styleFile( ":/qss/style.qss" );
    styleFile.open( QFile::ReadOnly );

    // Apply the loaded stylesheet
    QString style( styleFile.readAll() );
    app.setStyleSheet(style);
    app.setStyleSheet(style);

    // Set background color for the main window
    palette.setColor(QPalette::Window, QColor("#1e1d23"));
    palette.setColor(QPalette::WindowText, QColor("#a9b7c6"));

    // Set background color for QTextEdit and QPlainTextEdit
    palette.setColor(QPalette::Base, QColor("#1e1d23"));
    palette.setColor(QPalette::Text, QColor("#a9b7c6"));

    // Set button colors (normal and default)
    palette.setColor(QPalette::Button, QColor("#100E19"));
    palette.setColor(QPalette::ButtonText, QColor("#d3dae3"));

    // Set color for hover (using QPalette::AlternateBase for hover-like effect)
    palette.setColor(QPalette::AlternateBase, QColor("#C0DB50")); // Hover effect color

    // Set color for selection in QTableWidget
    palette.setColor(QPalette::Highlight, QColor("#04b97f"));
    palette.setColor(QPalette::HighlightedText, QColor("white"));

    // Set header background color in QTableWidget
    palette.setColor(QPalette::ToolTipBase, QColor("#323232"));
    palette.setColor(QPalette::ToolTipText, QColor("#a9b7c6"));
    app.setPalette(palette);

    MainWindow m_MainWindow;
    m_MainWindow.show();
    return app.exec();
}



