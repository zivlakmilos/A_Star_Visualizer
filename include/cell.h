#ifndef _CELL_H_
#define _CELL_H_

#include <QObject>

struct CellValue
{
    int state;
    int x;
    int y;
    int g;
    int h;
    int f;
};

class Cell : public QObject
{
    Q_OBJECT
    
public:
    Cell(QObject *parent = 0);
    ~Cell(void);
    
    enum State {
        StateFree = 0,
        StateBlock,
        StateStart,
        StateEnd,
        StateStep,
        StateError = -1
    };
    
    void toggleBlockState(void);
    
    /*
     * Getters and setters
     */
    
    inline State state(void) const { return m_state; };
    inline void state(State state) { m_state = state; };
    
private:
    State m_state;
};

#endif // _CELL_H_
