#include "Relationship.h"


Relationship::Relationship(Figure* firstFigure_): firstFigure{firstFigure_}
{}

Relationship::Relationship(Figure* firstFigure_, Figure* secondFigure_) : firstFigure{firstFigure_}, secondFigure{secondFigure_}
{}

void Relationship::draw(QPainter& painter)
{
    if (secondFigure != nullptr)
    {
        painter.drawLine( firstFigure->getCentralPosition(), secondFigure->getCentralPosition());
    }
    else
    {
        painter.drawLine( firstFigure->getCentralPosition(), endPoint);
    }
}

void Relationship::drawTemp(QPainter& painter)
{
    painter.drawLine( firstFigure->getCentralPosition(), endPoint);
}

void Relationship::setEndPoint(const QPoint& point)
{
    endPoint = point;
}

void Relationship::setFigures(Figure* firstFigure_, Figure* secondFigure_)
{
    firstFigure = firstFigure_;
    secondFigure = secondFigure_;
}
