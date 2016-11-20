#include "wastar.h"

#include <QtGui>

WAStar::WAStar(QWidget *parent)
    : QWidget(parent),
      m_table(nullptr),
      m_tool(ToolSelection)
{
    setMouseTracking(true);
    
    newMap(9, 9);
}

WAStar::~WAStar(void)
{
    clear();
}

void WAStar::newMap(int width, int height)
{
    clear();
    m_width = width;
    m_height = height;
    
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
            else if(cellState == Cell::StateStep)
                brush = Qt::DiagCrossPattern;
            
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

void WAStar::findPath(void)
{
    calculateStartValues();
    m_path.clear();
    
    for(CellValue nextStep = findBestStep(m_x, m_y);
        nextStep.state == Cell::StateFree;
        nextStep = findBestStep(m_x, m_y))
    {
        m_x = nextStep.x;
        m_y = nextStep.y;
        
        m_path.append(nextStep);
        m_table[nextStep.y * m_width + nextStep.x]->state(Cell::StateStep);
    }
    
    repaint();
}

CellValue WAStar::findBestStep(int x, int y)
{
    CellValue result;
    CellValue values[8];
    
    values[0] = calculate(x - 1, y - 1, 14);
    values[1] = calculate(x, y - 1, 10);
    values[2] = calculate(x + 1, y - 1, 14);
    values[3] = calculate(x + 1, y, 10);
    values[4] = calculate(x + 1, y + 1, 14);
    values[5] = calculate(x, y + 1, 10);
    values[6] = calculate(x - 1, y + 1, 14);
    values[7] = calculate(x - 1, y, 10);
    
    result.state = Cell::StateError;
    result.f = 10000;
    for(int i = 0; i < 8; i++)
        if(values[i].f < result.f && values[i].state & (Cell::StateFree | Cell::StateEnd))
            result = values[i];
    
    return result;
}

CellValue WAStar::calculate(int x, int y, int h)
{
    CellValue result;
    
    if(x < 0 || y < 0 ||
       x >= m_width || y >= m_height)
    {
        result.state = Cell::StateBlock;
    } else
    {
        result.state = m_table[y * m_width + x]->state();
        result.g = abs(m_endX - x) + abs(m_endY - y);
        result.h = h;
        result.f = result.g + result.h;
        result.x = x;
        result.y = y;
    }
    
    return result;
}

void WAStar::calculateStartValues(void)
{
    int founded = 0;
    for(int i = 0; i < m_width * m_height; i++)
    {
        Cell *cell = m_table[i];
        if(cell->state() == Cell::StateStart)
        {
            m_y = i / m_width;
            m_x = i % m_width;
            founded++;
        } else if(cell->state() == Cell::StateEnd)
        {
            m_endY = i / m_width;
            m_endX = i % m_width;
            founded++;
        }
        if(founded >= 2)
            break;
    }
}
