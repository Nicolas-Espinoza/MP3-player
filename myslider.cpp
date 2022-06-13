#include "myslider.h"

Myslider::Myslider(QWidget *parent) : QSlider (parent)
{

}

void Myslider::SetMax(qint64 value)
{
    setMaximum(value);
}

void Myslider::SetPos(qint64 value)
{
    setValue(value);
}
