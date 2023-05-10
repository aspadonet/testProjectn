#ifndef RELATIONSHIP_H
#define RELATIONSHIP_H

#include "Figure.h"

class Relationship
{
public:
    Relationship(Figure* firstFigure);
    Relationship(Figure* firstFigure, Figure* secondFigure);

    void draw(QPainter& painter);
    void drawTemp(QPainter& painter);
    void setEndPoint(const QPoint &point);
    void setFigures(Figure* firstFigure, Figure* secondFigure);

    Figure* firstFigure = nullptr;
    Figure* secondFigure = nullptr;
    QPoint endPoint;
};
#endif // RELATIONSHIP_H
