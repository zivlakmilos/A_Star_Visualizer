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
    for(int y = 0; y < m_height; y++)
        for(int x = 0; x < m_width; x++)
            m_table[y * m_width + x] = new Cell(x, y, this);
    m_table[m_height / 2 * m_width + 2]->state(Cell::StateStart);
    m_table[m_height / 2 * m_width + m_width - 3]->state(Cell::StateEnd);
    
    m_finish = false;
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
            if(cellState & (Cell::StateFree))
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
                brush = Qt::yellow;
            else if(cellState == Cell::StateChecked)
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

void WAStar::clean(void)
{
    for(int i = 0; i < m_width * m_height; i++)
    {
        if(m_table[i]->state() & (Cell::StateStep | Cell::StateChecked))
            m_table[i]->state(Cell::StateFree);
    }
}

void WAStar::mousePressEvent(QMouseEvent *event)
{
    QPoint pos = mapCoordsToGrid(event->pos());
    Cell *cell = m_table[pos.y() * m_width + pos.x()];
    
    if(m_finish)
    {
        clean();
        m_finish = false;
        return;
    }
    
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
    m_close.clear();
    m_open.clear();
    
    Cell *current = calculate(m_startX, m_startY, 0);
    m_close.append(current);
    
    bool cantFind = false;
    
    while(current->state() != Cell::StateEnd)
    {
        calculateNeighbors(current);
        
        if(!m_open.isEmpty())
        {
            int bestStepIndex = 0;
            Cell *bestStep = m_open[0];
            
            for(int i = 1; i < m_open.count(); i++)
            {
                if(m_open[i]->f() < bestStep->f())
                {
                    bestStep = m_open[i];
                    bestStepIndex = i;
                }
            }
            
            current = bestStep;
            m_close.append(current);
            m_open.remove(bestStepIndex);
            
            repaint();
        } else
        {
            cantFind = true;
            break;
        }
    }
    
    if(!cantFind)
    {
        current = current->parent();
        while(current->state() != Cell::StateStart)
        {
            current->state(Cell::StateStep);
            current = current->parent();
            repaint();
        }
    } else
    {
        QMessageBox::warning(this, tr("A* Visualizer"),
                             tr("Path doesn't exists"));
    }
    
    m_finish = true;
}

void WAStar::calculateNeighbors(Cell *current)
{
    Cell *values[8];
    
    int x = current->x();
    int y = current->y();
    int g = current->g();
    
    values[0] = calculate(x - 1, y - 1, g + 14);
    values[1] = calculate(x, y - 1, g + 10);
    values[2] = calculate(x + 1, y - 1, g + 14);
    values[3] = calculate(x + 1, y, g + 10);
    values[4] = calculate(x + 1, y + 1, g + 14);
    values[5] = calculate(x, y + 1, g + 10);
    values[6] = calculate(x - 1, y + 1, g + 14);
    values[7] = calculate(x - 1, y, g + 10);
    
    for(int i = 0 ; i < 8; i++)
    {
        if(values[i])
        {
            if(values[i]->state() == Cell::StateBlock)
                continue;
            
            if(i % 2 == 0)
            {
                int prev = i == 0 ? 7 : i - 1;
                int next = i == 7 ? 0 : i + 1;
                bool skip = false;
                
                if(values[prev])
                    if(values[prev]->state() == Cell::StateBlock)
                        skip = true;
                if(values[next])
                    if(values[next]->state() == Cell::StateBlock)
                        skip = true;
                
                if(skip)
                    continue;
            }
            
            if(values[i]->state() != Cell::StateStart &&
               values[i]->state() != Cell::StateEnd)
                values[i]->state(Cell::StateChecked);
                
            values[i]->parent(current);
            m_open.append(values[i]);
        }
    }
}

Cell *WAStar::calculate(int x, int y, int g)
{
    if(x < 0 || y < 0 ||
       x >= m_width || y >= m_height)
        return nullptr;
    
    Cell *result = m_table[y * m_width + x];
    
    if(result->state() == Cell::StateBlock)
        return result;
    if(result->state() == Cell::StateChecked &&
        result->g() <= g)
        return nullptr;
    
    result->h(abs(m_endX - x) + abs(m_endY - y));
    result->h(result->h() * 10);
    result->g(g);
    result->calculate();
    
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
            m_startY = i / m_width;
            m_startX = i % m_width;
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
