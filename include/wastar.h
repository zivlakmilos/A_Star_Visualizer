#ifndef _W_STAR_H_
#define _W_STAR_H_

#include <QWidget>

class Cell;

class WAStar : public QWidget
{
    Q_OBJECT
    
public:
    WAStar(QWidget *parent = 0);
    virtual ~WAStar(void);
    
    enum Tool {
        ToolSelection,
        ToolToggleBlock,
        ToolMoveStart,
        ToolMoveEnd
    };
    
    virtual QSize sizeHint(void) const override;
    
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    
protected:
    virtual void paintEvent(QPaintEvent *event);
    
private:
    void clear(void);
    QPoint mapCoordsToGrid(const QPoint &position);
    
    int m_width;
    int m_height;
    
    Cell **m_table;
    
    Tool m_tool;
    QPoint m_oldPos;
    
public slots:
    void newMap(void);
};

#endif // _W_STAR_H_
