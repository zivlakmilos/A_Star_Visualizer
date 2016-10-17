#include "mainwindow.h"

#include <QCoreApplication>
#include <QtGui>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    /*
     * Setting application parameters
     */
    QCoreApplication::setApplicationName(tr("A Star Visualizer"));
    QCoreApplication::setOrganizationName(tr("Milos Zivlak - ZI"));
    QCoreApplication::setOrganizationDomain(tr("http://zivlakmilos.ddns.net"));
    
    setWindowTitle(QString("%1    %2 %3 2016").arg(QCoreApplication::applicationName(),
                                             QChar(0xA9),   // Copyright simbol (ASCII)
                                             QCoreApplication::organizationName()));
}

MainWindow::~MainWindow(void)
{
}
