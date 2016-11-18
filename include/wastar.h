#ifndef _W_STAR_H_
#define _W_STAR_H_

#include <QWidget>

class WAStar : public QWidget
{
    Q_OBJECT
    
public:
    WAStar(QWidget *parent = 0);
    virtual ~WAStar(void);
    
    virtual QSize sizeHint(void) const override;
    
protected:
    virtual void paintEvent(QPaintEvent *event);
    
private:
    int m_width;
    int m_height;
    
public slots:
    void newMap(void);
};

#endif // _W_STAR_H_
