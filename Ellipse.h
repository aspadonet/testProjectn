#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "Figure.h"

class Ellipse : public Figure
{
public:
    Ellipse(QPoint startPoint, QPoint endPoint, int id = 0);

    void draw(QPainter& painter) override;
    QRect getBoundingArea() override;

    QString GetName() override;
};

#endif // ELLIPSE_H
