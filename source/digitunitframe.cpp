#include "digitunitframe.h"

DigitUnitFrame::DigitUnitFrame(QString unit, bool isEditable)
{

    setFrameStyle(QFrame::Plain | QFrame::StyledPanel);

    _unit = new QLabel(unit);
    _val = new QSpinBox();
    _val->setAlignment(Qt::AlignCenter);
    _val->setFrame(false);
    _val->setReadOnly(!isEditable);
    _val->setButtonSymbols(QAbstractSpinBox::NoButtons);
    _val->setStyleSheet("background-color:transparent");

    QHBoxLayout *layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 5, 0);
    layout->addWidget(_val, 1);
    layout->addWidget(_unit);

    setLayout(layout);
}

void DigitUnitFrame::setFont(QFont font)
{
    _unit->setFont(font);
    _val->setFont(font);
}
void DigitUnitFrame::setHeight(int height)
{
    setFixedHeight(height);
}

int DigitUnitFrame::value()
{
    return _val->value();
}

void DigitUnitFrame::setValue(int value)
{
    _val->setValue(value);
}
