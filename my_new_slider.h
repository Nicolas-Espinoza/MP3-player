#ifndef MY_NEW_SLIDER_H
#define MY_NEW_SLIDER_H
#include <QSlider>

class my_new_slider
{
    Q_OBJECT

public:
    my_new_slider (QWidget *parent = nullptr);
public slots:
    void SetMax(qint64 value);
    void SetPos(qint64 value);
};

#endif // MY_NEW_SLIDER_H
