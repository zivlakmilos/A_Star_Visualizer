#include "wastar.h"

#include <QtGui>

#include "cell.h"

WAStar::WAStar(QWidget *parent)
    : QWidget(parent),
      m_width(9),
      m_height(9),
      m_table(nullptr),
      m_tool(ToolSelection)
{
    setMouseTracking(true);
    
    newMap();
}

WAStar::~WAStar(void)
{
    clear();
}

void WAStar::newMap(void)
{
    clear();
    
    m_table = new Cell*[m_width * m_height];
    for(int i = 0; i < m_width * m_height; i++)
        m_table[i] = new Cell(this);
    m_table[m_height / 2 * m_width + 2]->state(Cell::StateStart);
    m_table[m_height / 2 * m_width + m_width - 3]->state(Cell::StateEnd);
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
    
    /*
     * Draw cells
     */
    for(int i = 0; i < m_height; i++)
    {
        for(int j = 0; j < m_width; j++)
        {
            Cell::State cellState = m_table[i * m_width + j]->state();
            if(cellState == Cell::StateFree)
                continue;
            
            QBrush brush = Qt::black;
            QRect rect(j * width() / m_width,
                       i * height() / m_height,
                       width() / m_width,
                       height() / m_height);
            
            if(cellState == Cell::StateStart)
                brush = Qt::red;
            else if(cellState == Cell::StateEnd)
                brush = Qt::blue;
            
            painter.setBrush(brush);
            painter.drawRect(rect);
        }
    }
}

QSize WAStar::sizeHint(void) const
{
    return QSize(m_width * 50, m_height * 50);
}

void WAStar::clear(void)
{
    if(m_table)
    {
        for(int i = 0; i < m_width * m_height; i++)
            if(m_table[i])
                delete m_table[i];
        delete[] m_table;
    }
}

void WAStar::mousePressEvent(QMouseEvent *event)
{
    QPoint pos = mapCoordsToGrid(event->pos());
    Cell *cell = m_table[pos.y() * m_width + pos.x()];
    
    switch(cell->state())
    {
        case Cell::StateFree:
        case Cell::StateBlock:
            m_tool = ToolToggleBlock;
            cell->toggleBlockState();
            break;
        case Cell::StateStart:
            m_tool = ToolMoveStart;
            break;
        case Cell::Cell::StateEnd:
            m_tool = ToolMoveEnd;
            break;
    }
    
    m_oldPos = pos;
    repaint();
    event->accept();
}

void WAStar::mouseReleaseEvent(QMouseEvent *event)
{
    m_tool = ToolSelection;
    
    m_oldPos = mapCoordsToGrid(event->pos());
    repaint();
    event->accept();
}

void WAStar::mouseMoveEvent(QMouseEvent *event)
{
    QPoint pos = mapCoordsToGrid(event->pos());
    
    if(pos != m_oldPos)
    {
        Cell *cell = m_table[pos.y() * m_width + pos.x()];
        Cell *oldCell = m_table[m_oldPos.y() * m_width + m_oldPos.x()];
        if(m_tool == WAStar::ToolToggleBlock)
            cell->toggleBlockState();
        else if(m_tool == WAStar::ToolMoveStart)
        {
            if(cell->state() != Cell::StateFree)
                return;
            
            cell->state(Cell::StateStart);
            oldCell->state(Cell::StateFree);
        } else if(m_tool == WAStar::ToolMoveEnd)
        {
            if(cell->state() != Cell::StateFree)
                return;
            
            cell->state(Cell::StateEnd);
            oldCell->state(Cell::StateFree);
        }
    }
    
    m_oldPos = pos;
    repaint();
    event->accept();
}

QPoint WAStar::mapCoordsToGrid(const QPoint &position)
{
    if(position.x() < 0 || position.x() > width() ||
       position.y() < 0 || position.y() > height())
        return m_oldPos;
    
    QPoint pos;
    pos.setX(position.x() * m_width / width());
    pos.setY(position.y() * m_height / height());
    
    return pos;
}
