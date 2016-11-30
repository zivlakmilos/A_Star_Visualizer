#include "cell.h"

Cell::Cell(int x, int y, QObject *parent)
    : QObject(parent),
      m_state(Cell::StateFree),
      m_x(x),
      m_y(y),
      m_g(0),
      m_h(0),
      m_f(0),
      m_parent(nullptr)
{
}

Cell::~Cell(void)
{
}

void Cell::toggleBlockState(void)
{
    if(m_state == Cell::StateFree)
        state(Cell::StateBlock);
    else if(m_state == Cell::StateBlock)
        state(Cell::StateFree);
}

void Cell::calculate(void)
{
    m_f = m_g + m_h;
}
