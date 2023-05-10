#include "Figure.h"


int Figure::idCounter = 0;


Figure::Figure(QPoint startPoint, QPoint endPoint, int id_): startPoint(startPoint), endPoint(endPoint), id(id_)
{
    if(id == 0)
    {
        idCounter++;
        id = idCounter;
    }
    setLengthSidesRectangle();
    recalculateCentralPosition();    
}

QPoint Figure::getCentralPosition()
{
    return CentralPosition;
}

QPoint Figure::getStartPoint()
{
    return startPoint;
}

QPoint Figure::getEndPoint()
{
    return endPoint;
}

void Figure::setCentralPosition(QPoint position)
{
    CentralPosition = position;
}

void Figure::setPosAfterMoving(QPoint position)
{
    setCentralPosition(position);
    restoreStartEndPoints();
}

void Figure::setStartPoint(const QPoint& point)
{
    startPoint = point;
}

void Figure::setEndPoint(const QPoint& point)
{
    endPoint = point;
    setLengthSidesRectangle();
    recalculateCentralPosition();
}

void Figure::setLengthSidesRectangle()
{
    lengthSideRectangleX = (endPoint.x() - startPoint.x());
    lengthSideRectangleY = (endPoint.y() - startPoint.y());
}

void Figure::recalculateCentralPosition()
{
    CentralPosition.setX(lengthSideRectangleX / 2 + startPoint.x());
    CentralPosition.setY(lengthSideRectangleY / 2 + startPoint.y());
}

void Figure::restoreStartEndPoints()
{
    startPoint.setX(CentralPosition.x() - lengthSideRectangleX/2);
    startPoint.setY(CentralPosition.y() - lengthSideRectangleY/2);
    endPoint.setX(CentralPosition.x() + lengthSideRectangleX/2);
    endPoint.setY(CentralPosition.y() + lengthSideRectangleY/2);
}

int Figure::getId(){
    return id;
}

void Figure::setColor(const QColor& color)
{
    pen.setColor(color);
}
