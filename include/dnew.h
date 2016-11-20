#ifndef _D_NEW_H_
#define _D_NEW_H_

#include <QDialog>

class QSpinBox;

class DNew : public QDialog
{
    Q_OBJECT
    
public:
    explicit DNew(QWidget *parent = 0);
    virtual ~DNew(void);
    
    void size(int *width, int *height);
    
private:
    void setupGui(void);
    
    QSpinBox *m_sbWidth;
    QSpinBox *m_sbHeight;
};

#endif // _D_NEW_H_
