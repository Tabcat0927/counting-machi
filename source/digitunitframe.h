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
#include <QFont>

class DigitUnitFrame : public QFrame
{
    Q_OBJECT
public:
    DigitUnitFrame(QString, bool, int, int);
    void setFont(const QFont);
    void setHeight(const int);
    int value();
    void setValue(const int);

private:
    QLabel      *_unit;
    QSpinBox    *_val;
};

#endif // DIGITUNITFRAME_H
