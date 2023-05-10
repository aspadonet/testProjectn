#ifndef FIGURE_H
#define FIGURE_H

#include <QPainter>

class Figure
{

public:
    Figure(QPoint startPoint, QPoint endPoint, int id_);

    virtual QString GetName() = 0;
    virtual ~Figure(){};

    virtual void draw(QPainter& painter) = 0;
    virtual QRect getBoundingArea() = 0;

    QPoint getCentralPosition();
    QPoint getStartPoint();
    QPoint getEndPoint();

    void setCentralPosition(QPoint position);
    void setPosAfterMoving(QPoint position);
    void setStartPoint(const QPoint& point);
    void setEndPoint(const QPoint& point);
    void setLengthSidesRectangle();

    void recalculateCentralPosition();
    void restoreStartEndPoints();

    int getId();

    void setColor(const QColor& color);

protected:
    QPoint CentralPosition;
    QPoint startPoint;
    QPoint endPoint;
    int id = 0;
    static int idCounter;
    int lengthSideRectangleX;
    int lengthSideRectangleY;
    QPen pen;
};

enum FigureType
{
    FigureRectangle = 1,
    FigureTriangle,
    FigureEllipse,
};


#endif // FIGURE_H
