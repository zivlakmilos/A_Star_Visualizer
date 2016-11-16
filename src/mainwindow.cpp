#include "mainwindow.h"

#include <QCoreApplication>
#include <QtGui>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    /*
     * Setting core application parameters
     */
    QCoreApplication::setApplicationName(tr("A Star Visualizer"));
    QCoreApplication::setOrganizationName(tr("Milos Zivlak - ZI"));
    QCoreApplication::setOrganizationDomain(tr("http://zivlakmilos.ddns.net"));
    
    /*
     * Setting window title
     */
    setWindowTitle(QString("%1    %2 %3 2016").arg(QCoreApplication::applicationName(),
                                             QChar(0xA9),   // Copyright simbol (ASCII)
                                             QCoreApplication::organizationName()));
    
    /*
     * Setup GUI
     */
    setupGui();
}

MainWindow::~MainWindow(void)
{
}

void MainWindow::setupGui(void)
{
    /*
     * Setup menus
     */
    setupMenus();
    
    /*
     * Setup toolbar
     */
    
    /*
     * Status bar
     */
    statusBar();
    
    /*
     * Setup main widget
     */
}

void MainWindow::setupMenus(void)
{
    /*
     * Setup actions
     */
    
    m_actionFileNew = new QAction(tr("&New"), this);
    m_actionFileNew->setShortcut(Qt::Key_N | Qt::CTRL);
    
    m_actionHelpAbout = new QAction(tr("&About"), this);
    
    m_actionFileQuit = new QAction(tr("&Quit"), this);
    m_actionFileQuit->setShortcut(Qt::Key_Q | Qt::CTRL);
    connect(m_actionFileQuit, SIGNAL(triggered(bool)),
            qApp, SLOT(quit()));
    
    /*
     * Setup menus
     */
    
    QMenu *menuFile = menuBar()->addMenu(tr("&File"));
    menuFile->addAction(m_actionFileNew);
    menuFile->addSeparator();
    menuFile->addAction(m_actionFileQuit);
    
    QMenu *menuHelp = menuBar()->addMenu(tr("&Help"));
    menuHelp->addAction(m_actionHelpAbout);
}
