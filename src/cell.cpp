#include "cell.h"

Cell::Cell(QObject *parent)
    : QObject(parent),
      m_state(Cell::StateFree),
      m_g(0),
      m_h(0),
      m_f(0)
{
}

Cell::~Cell(void)
{
}

void Cell::calculate(void)
{
    m_f = m_g + m_h;
}

void Cell::toggleBlockState(void)
{
    if(m_state == Cell::StateFree)
        m_state = Cell::StateBlock;
    else if(m_state == Cell::StateBlock)
        m_state = Cell::StateFree;
}
