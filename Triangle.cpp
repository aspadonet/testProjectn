#include "Triangle.h"
#include <cmath>


Triangle::Triangle(QPoint startPoint, QPoint endPoint, int id ) : Figure(startPoint, endPoint, id)
{}

QString Triangle::GetName()
{
    return "Triangle";
}

void Triangle::draw(QPainter& painter)
{
    painter.setPen(pen);

    int rx = abs(lengthSideRectangleX / 2);
    int ry = abs(lengthSideRectangleY / 2);
    int r = std::min(rx, ry);

    double x1 = CentralPosition.x() + r*cos(-M_PI/2);
    double y1 = CentralPosition.y() + r*sin(-M_PI/2);
    double x2 = CentralPosition.x() + r*cos(2*M_PI/3-M_PI/2);
    double y2 = CentralPosition.y() + r*sin(2*M_PI/3-M_PI/2);
    double x3 = CentralPosition.x() + r*cos(4*M_PI/3-M_PI/2);
    double y3 = CentralPosition.y() + r*sin(4*M_PI/3-M_PI/2);

    painter.drawLine(x1, y1, x2, y2);
    painter.drawLine(x2, y2, x3, y3);
    painter.drawLine(x3, y3, x1, y1);
}

QRect Triangle::getBoundingArea()
{
    return QRect(CentralPosition.x() - lengthSideRectangleX / 2,
                 CentralPosition.y() - lengthSideRectangleY / 2,
                 lengthSideRectangleX,
                 lengthSideRectangleY);
}
