#include "digitunitframe.h"

DigitUnitFrame::DigitUnitFrame(QString unit, bool isEditable, int min, int max)
{//为什么在这个类里设置的字体和在外面设置的相同字体显示不一样

    setFrameStyle(QFrame::Plain | QFrame::StyledPanel);

    _unit = new QLabel(unit);
    //_unit->setFont(font);
    _val = new QSpinBox();
    //_val->setFont(QFont("微软雅黑", 15));
    _val->setMinimum(min);
    _val->setMaximum(max);
    _val->setAlignment(Qt::AlignCenter);
    _val->setFrame(false);
    _val->setReadOnly(!isEditable);
    _val->setButtonSymbols(QAbstractSpinBox::NoButtons);
    _val->setStyleSheet("background-color:transparent");

    QHBoxLayout *layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 5, 0);
    layout->addWidget(_val, 1);
    layout->addWidget(_unit);

    //setFont(QFont("微软雅黑", 15));
    setLayout(layout);
}

void DigitUnitFrame::setFont(const QFont font)
{
    _unit->setFont(font);
    _val->setFont(font);
}
void DigitUnitFrame::setHeight(const int height)
{
    setFixedHeight(height);
}

int DigitUnitFrame::value()
{
    return _val->value();
}

void DigitUnitFrame::setValue(const int value)
{
    _val->setValue(value);
}
