#include "digitunitframe.h"

DigitUnitFrame::DigitUnitFrame(QString unit, bool isEditable)
{
    _unit = new QLabel(unit);

    _val = new QLineEdit();
    _val->setAlignment(Qt::AlignCenter);
    _val->setFrame(false);
    _val->setReadOnly(!isEditable);
    _val->setStyleSheet("background-color:transparent");
    QIntValidator *valid = new QIntValidator();
    _val->setValidator(valid);

    setFrameStyle(QFrame::Plain | QFrame::StyledPanel);

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
