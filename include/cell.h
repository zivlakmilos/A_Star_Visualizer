#ifndef _CELL_H_
#define _CELL_H_

#include <QObject>

class Cell : public QObject
{
    Q_OBJECT
    
public:
    Cell(QObject *parent = 0);
    ~Cell(void);
    
    enum State {
        StateFree,
        StateBlock,
        StateStart,
        StateEnd
    };
    
    void calculate(void);
    
    /*
     * Getters and setters
     */
    
    inline State state(void) const { return m_state; };
    inline void state(State state) { m_state = state; };
    
    inline int g(void) const { return m_g; };
    inline void g(int g) { m_g = g; };
    
    inline int h(void) const { return m_h; };
    inline void h(int h) { m_h = h; };
    
    inline int f(void) const { return m_f; };
    inline void f(int f) { m_f = f; };
    
private:
    State m_state;
    int m_g;
    int m_h;
    int m_f;
};

#endif // _CELL_H_
