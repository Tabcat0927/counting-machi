#ifndef DIGITUNITFRAME_H
#define DIGITUNITFRAME_H

#include <QString>
#include <QLineEdit>
#include <QFrame>
#include <QLabel>
#include <QHBoxLayout>
#include <QFont>
#include <QIntValidator>
#include <QSpinBox>

class DigitUnitFrame : public QFrame
{
    Q_OBJECT
public:
    DigitUnitFrame(QString unit, bool isEditable);
    void setFont(QFont);
    void setHeight(int);
    int value();
    void setValue(int);

private:
    QLabel      *_unit;
    QSpinBox    *_val;
};

#endif // DIGITUNITFRAME_H
