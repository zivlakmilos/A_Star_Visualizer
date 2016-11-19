#include "cell.h"

Cell::Cell(QObject *parent)
    : QObject(parent),
      m_state(Cell::StateFree)
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
