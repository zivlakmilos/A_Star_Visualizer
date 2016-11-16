#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

#include <QMainWindow>

class MainWindow : public QMainWindow
{
public:
    MainWindow(QWidget *parent = 0);
    virtual ~MainWindow(void);
    
private:
    void setupGui(void);
    void setupMenus(void);
    
    QAction *m_actionFileNew;
    QAction *m_actionFileQuit;
    
    QAction *m_actionHelpAbout;
};

#endif // _MAIN_WINDOW_H_
