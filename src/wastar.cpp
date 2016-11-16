#include "wastar.h"

#include <QtGui>

WAStar::WAStar(QWidget *parent)
    : QWidget(parent),
      m_width(9),
      m_height(9)
{
    newMap();
}

WAStar::~WAStar(void)
{
}

void WAStar::newMap(void)
{
}

void WAStar::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    int i;
    int x, y;
    
    /*
     * Draw grid
     */
    for(int i = 1; i < m_width; i++)
    {
        x = i * width() / m_width;
        painter.drawLine(x, 0,
                         x, height());
    }
    for(int i = 1; i < m_height; i++)
    {
        y = i * height() / m_height;
        painter.drawLine(0, y,
                         width(), y);
    }
}

QSize WAStar::sizeHint(void) const
{
    return QSize(m_width * 50, m_height * 50);
}
