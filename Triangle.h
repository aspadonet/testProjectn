#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Figure.h"

class Triangle : public Figure
{
public:
    Triangle(QPoint startPoint, QPoint endPoint, int id = 0);

    virtual void draw(QPainter& painter) override;
    QRect getBoundingArea() override;

    QString GetName() override;
};

#endif // TRIANGLE_H
