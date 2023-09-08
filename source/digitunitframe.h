#ifndef DIGITUNITFRAME_H
#define DIGITUNITFRAME_H

#include <QString>
#include <QLineEdit>
#include <QFrame>
#include <QLabel>
#include <QHBoxLayout>
#include <QFont>
#include <QIntValidator>

class DigitUnitFrame : public QFrame
{
    Q_OBJECT
public:
    DigitUnitFrame(QString unit, bool isEditable);
    void setFont(QFont font);
    void setHeight(int height);

private:
    QLabel      *_unit;
    QLineEdit   *_val;
};

#endif // DIGITUNITFRAME_H
