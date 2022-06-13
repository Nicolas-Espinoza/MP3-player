#ifndef MYSLIDER_H
#define MYSLIDER_H
#include <QSlider>

class Myslider : public QSlider
{
    Q_OBJECT

public:
    Myslider (QWidget *parent = nullptr);
public slots:
    void SetMax(qint64 value);
    void SetPos(qint64 value);
};

#endif // MYSLIDER_H
