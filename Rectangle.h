#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Figure.h"

class Rectangle : public Figure
{
public:
    Rectangle(QPoint startPoint, QPoint endPoint, int id = 0);

    void draw(QPainter& painter) override;
    QRect getBoundingArea() override;

    QString GetName() override;
};

#endif // RECTANGLE_H
