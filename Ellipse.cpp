#include "Ellipse.h"


Ellipse::Ellipse(QPoint startPoint, QPoint endPoint, int id ) : Figure(startPoint, endPoint, id)
{}

QString Ellipse::GetName()
{
    return "Ellipse";
}

void Ellipse::draw(QPainter& painter)
{
    painter.setPen(pen);

    painter.drawEllipse(CentralPosition.x() - lengthSideRectangleX/2,
                        CentralPosition.y() - lengthSideRectangleY/2,
                        lengthSideRectangleX,
                        lengthSideRectangleY);
}

QRect Ellipse::getBoundingArea()
{
    return QRect(CentralPosition.x() - lengthSideRectangleX / 2,
                 CentralPosition.y() - lengthSideRectangleY / 2,
                 lengthSideRectangleX,
                 lengthSideRectangleY);
}


