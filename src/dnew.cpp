#include "dnew.h"

#include <QtGui>

DNew::DNew(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("New"));
    
    setupGui();
}

DNew::~DNew(void)
{
}

void DNew::setupGui(void)
{
    /*
     * Setup components
     */
    
    QLabel *lblWidth = new QLabel(tr("Width:"), this);
    QLabel *lblHeight = new QLabel(tr("Height:"), this);
    
    m_sbWidth = new QSpinBox(this);
    m_sbWidth->setRange(9, 50);
    m_sbWidth->setValue(9);
    
    m_sbHeight = new QSpinBox(this);
    m_sbHeight->setRange(9, 50);
    m_sbHeight->setValue(9);
    
    QPushButton *btnOk = new QPushButton(tr("&Ok"), this);
    btnOk->setDefault(true);
    connect(btnOk, SIGNAL(clicked(bool)),
            this, SLOT(accept()));
    
    QPushButton *btnCancel = new QPushButton(tr("&Cancel"), this);
    connect(btnCancel, SIGNAL(clicked(bool)),
            this, SLOT(reject()));
    
    /*
     * Setup layouts
     */
    
    QVBoxLayout *layoutMain = new QVBoxLayout(this);
    QGridLayout *layoutInput = new QGridLayout;
    QHBoxLayout *layoutButtons = new QHBoxLayout;
    
    /*
     * Lay down components
     */
    
    layoutInput->addWidget(lblWidth, 0, 0);
    layoutInput->addWidget(m_sbWidth, 0, 1);
    layoutInput->addWidget(lblHeight, 1, 0);
    layoutInput->addWidget(m_sbHeight, 1, 1);
    
    layoutButtons->addWidget(btnOk);
    layoutButtons->addWidget(btnCancel);
    
    layoutMain->addLayout(layoutInput);
    layoutMain->addLayout(layoutButtons);
}

void DNew::size(int *width, int *height)
{
    *width = m_sbWidth->value();
    *height = m_sbHeight->value();
}
