#include "mainwindow.h"

#include <QCoreApplication>
#include <QtGui>

#include "wastar.h"
#include "dnew.h"

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
     * Setup main widget
     */
    m_centralWidget = new WAStar(this);
    setCentralWidget(m_centralWidget);
    
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
}

void MainWindow::setupMenus(void)
{
    /*
     * Setup actions
     */
    
    m_actionFileNew = new QAction(tr("&New"), this);
    m_actionFileNew->setShortcut(Qt::Key_N | Qt::CTRL);
    connect(m_actionFileNew, SIGNAL(triggered(bool)),
            this, SLOT(newMap()));
    
    m_actionFileStart = new QAction(tr("&Start"), this);
    m_actionFileStart->setShortcut(Qt::Key_S | Qt::CTRL);
    connect(m_actionFileStart, SIGNAL(triggered(bool)),
            m_centralWidget, SLOT(findPath()));
    
    m_actionHelpAbout = new QAction(tr("&About"), this);
    m_actionHelpAbout->setShortcut(Qt::Key_F1);
    connect(m_actionHelpAbout, SIGNAL(triggered(bool)),
            this, SLOT(about()));
    
    m_actionFileQuit = new QAction(tr("&Quit"), this);
    m_actionFileQuit->setShortcut(Qt::Key_Q | Qt::CTRL);
    connect(m_actionFileQuit, SIGNAL(triggered(bool)),
            qApp, SLOT(quit()));
    
    /*
     * Setup menus
     */
    
    QMenu *menuFile = menuBar()->addMenu(tr("&File"));
    menuFile->addAction(m_actionFileNew);
    menuFile->addAction(m_actionFileStart);
    menuFile->addSeparator();
    menuFile->addAction(m_actionFileQuit);
    
    QMenu *menuHelp = menuBar()->addMenu(tr("&Help"));
    menuHelp->addAction(m_actionHelpAbout);
}

void MainWindow::newMap(void)
{
    DNew *dlgNew = new DNew(this);
    
    if(dlgNew->exec() == QDialog::Accepted)
    {
        int width, height;
        dlgNew->size(&width, &height);
        
        m_centralWidget->newMap(width, height);
    }
}

void MainWindow::about(void)
{
    QString msg = tr("<b>%1</b><hr /><br />"
                     "site:     %2<br />"
                     "github:   %3<br />"
                     "linkedin: %4<br />"
                     "email:    %5<br />"
                     "phone:    %6").arg(QCoreApplication::organizationName(),
                                         QCoreApplication::organizationDomain(),
                                         tr("https://github.com/zivlakmilos/"),
                                         tr("https://rs.linkedin.com/in/zivlakmilos/"),
                                         tr("zivlakmilos@gmail.com"),
                                         tr("061/668-3739"));
    
    QMessageBox::about(this, QCoreApplication::applicationName(), msg);
}
