#ifndef _W_STAR_H_
#define _W_STAR_H_

#include <QWidget>

#include "cell.h"
#include "doublelinkedlist.h"

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
    
    void calculateStartValues(void);
    CellValue findBestStep(int x, int y);
    CellValue calculate(int x, int y, int h);
    
    int m_width;
    int m_height;
    
    Cell **m_table;
    DoubleLinkedList<CellValue> m_path;
    
    Tool m_tool;
    QPoint m_oldPos;
    
    int m_x;
    int m_y;
    int m_endX;
    int m_endY;
    
public slots:
    void newMap(int width, int height);
    void findPath(void);
};

#endif // _W_STAR_H_
