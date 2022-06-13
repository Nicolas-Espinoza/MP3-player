#include "my_new_slider.h"

my_new_slider::my_new_slider(QWidget *parent)
{

}
void Myslider::SetMax(qint64 value)
{
    setMaximum(value);
}

void ::SetPos(qint64 value)
{
    setValue(value);
}
