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
    Cell(int x, int y, QObject *parent = 0);
    ~Cell(void);
    
    enum State {
        StateFree =         0x0001,
        StateBlock =        0x0002,
        StateStart =        0x0004,
        StateEnd =          0x0008,
        StateStep =         0x0010,
        StateChecked =      0x0020,
        StateError =        0x0100
    };
    
    void toggleBlockState(void);
    void calculate(void);
    
    /*
     * Getters and setters
     */
    
    inline const State &state(void) const { return m_state; };
    inline void state(const State &state) { m_state = state; };
    
    inline const int &x(void) const { return m_x; };
    inline void x(const int &x) { m_x = x; };
    
    inline const int &y(void) const { return m_y; };
    inline void y(const int &y) { m_y = y; };
    
    inline const int &g(void) const { return m_g; };
    inline void g(const int &g) { m_g = g; };
    
    inline const int &h(void) const { return m_h; };
    inline void h(const int &h) { m_h = h; };
    
    inline const int &f(void) const { return m_f; };
    inline void f(const int &f) { m_f = f; };
    
    inline Cell *parent(void) const { return m_parent; };
    inline void parent(Cell *parent) { m_parent = parent; };
    
private:
    State m_state;
    int m_x;
    int m_y;
    int m_g;
    int m_h;
    int m_f;
    
    Cell *m_parent;
};

#endif // _CELL_H_
