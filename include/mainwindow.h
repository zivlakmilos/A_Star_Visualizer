#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

#include <QMainWindow>

class WAStar;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    virtual ~MainWindow(void);
    
private:
    void setupGui(void);
    void setupMenus(void);
    
    QAction *m_actionFileNew;
    QAction *m_actionFileStart;
    QAction *m_actionFileQuit;
    
    QAction *m_actionHelpAbout;
    
    WAStar *m_centralWidget;
    
private slots:
    void newMap(void);
    void about(void);
};

#endif // _MAIN_WINDOW_H_
