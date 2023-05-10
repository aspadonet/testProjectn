#include "Rectangle.h"


Rectangle::Rectangle(QPoint startPoint, QPoint endPoint, int id) : Figure(startPoint, endPoint, id)
{}

QString Rectangle::GetName()
{
    return "Rectangle";
}

void Rectangle::draw(QPainter &painter)
{
     painter.setPen(pen);
     painter.drawRect(getBoundingArea());
}

QRect Rectangle::getBoundingArea()
{
    return QRect(CentralPosition.x() - lengthSideRectangleX / 2,
                 CentralPosition.y() - lengthSideRectangleY / 2,
                 lengthSideRectangleX,
                 lengthSideRectangleY);
}
