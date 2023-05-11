
#include "Canvas.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "Triangle.h"
#include <QMessageBox>
#include <QMouseEvent>
#include <algorithm>
#include "qdebug.h"

Canvas::Canvas(QWidget* parent) : QWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);
    setCursor(Qt::ArrowCursor);
}

Canvas::~Canvas()
{
    for(Figure* fig : figuresVec)
        delete fig ;

    for(Relationship* relationship : relationshipsVec)
        delete relationship;
}

void Canvas::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    for(Relationship* relationship : relationshipsVec)
        relationship->draw(painter);

    for(Figure* fig : figuresVec)
        fig->draw(painter);

    if (newRelationship != nullptr)
    {
        newRelationship->draw(painter);
    }
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        switch(drawOption)
        {
        case DeleteFigureOption:
            beginDeleteFigure(event->pos());
            break;
        case MoveFigureOption:
            beginMoveFigure(event->pos());
            break;
        case DrawRelationshipOption:
            beginDrawRelationship(event->pos());
            break;
        case DrawFigureOption:
            beginDrawFigure(event->pos());
            break;
        }

        repaint();
    }
    else if(event->button() == Qt::RightButton)
    {
        cancelOperation();
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if (isDrawing)
    {
        newFigure->setEndPoint(event->pos());
        repaint();
    }
    else if(beingMovedFigure)
    {
        setCursor(Qt::PointingHandCursor);

        beingMovedFigure->setPosAfterMoving(event->pos());
        repaint();
    }
    else if (isDrawRelationshipOption && newRelationship != nullptr)
    {
        newRelationship->setEndPoint(event->pos());
        repaint();
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (isDrawing && event->button() == Qt::LeftButton)
    {
            newFigure->setEndPoint(event->pos());

            isDrawing = false;
            newFigure = nullptr;

            repaint();
    }
    else if(beingMovedFigure)
    {
        setCursor(Qt::ArrowCursor);

        beingMovedFigure->setPosAfterMoving(event->pos());
        beingMovedFigure->setColor(Qt::black);
        beingMovedFigure = nullptr;

        repaint();
    }
    else if (isDrawRelationshipOption && newRelationship != nullptr)
    {
        newRelationship->setEndPoint(event->pos());

        repaint();
    }
}

void Canvas::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        cancelOperation();
    }
}

void Canvas::initialOptionDrawFigure(FigureType figure)
{
    setCursor(Qt::ArrowCursor);

    drawOption = DrawFigureOption;
    ActiveFigure = figure;
    firstRelationshipFigure = nullptr;
}

void Canvas::initialOptionFigureMove()
{
    drawOption = MoveFigureOption;
    firstRelationshipFigure = nullptr;
}

void Canvas::initialOptionDrawRelationship()
{
    setMouseTracking(true);
    setCursor(Qt::ArrowCursor);

    drawOption = DrawRelationshipOption;
}

void Canvas::initialOptionDeleteFigure()
{
    setCursor(Qt::ArrowCursor);

    drawOption = DeleteFigureOption;
    firstRelationshipFigure = nullptr;
}

std::vector<Figure*>& Canvas::getVectorFigure()
{
    return figuresVec;
}

void Canvas::setVectorFigure(const std::vector<Figure*>& figuresVec_)
{
    for(Figure* fig : figuresVec)
        delete fig;

    figuresVec = figuresVec_;
}

std::vector<Relationship*>& Canvas::getVectorRelationship()
{
    return relationshipsVec;
}

void Canvas::setVectorRelationship(const std::vector<Relationship*>& relationshipsVec_)
{
    for(Relationship* relationship : relationshipsVec)
        delete relationship ;

    relationshipsVec = relationshipsVec_;
}

void Canvas::beginDeleteFigure(QPoint pos)
{
    Figure* fig = getFigureInPosition(pos);
    if(fig)
        deleteFigure(fig);
}

void Canvas::beginMoveFigure(QPoint pos)
{
    //setCursor(Qt::PointingHandCursor);
    beingMovedFigure = getFigureInPosition(pos);
    if (beingMovedFigure)
    {
        beingMovedFigure->setColor(Qt::red);
        setCursor(Qt::PointingHandCursor);
    }
}

void Canvas::beginDrawRelationship(QPoint pos)
{
    isDrawRelationshipOption = true;

    if(!firstRelationshipFigure)
    {
        firstRelationshipFigure = getFigureInPosition(pos);
        if (firstRelationshipFigure != nullptr)
        {
            newRelationship = new Relationship(firstRelationshipFigure);
            newRelationship->setEndPoint(pos);
            repaint();
        }
    }
    else
    {
        Figure* secondRelationshipFigure = getFigureInPosition(pos);
        if(!secondRelationshipFigure)
            firstRelationshipFigure = nullptr;
        isDrawRelationshipOption = false;
        delete  newRelationship;
        newRelationship = nullptr;
        repaint();

        if(firstRelationshipFigure && secondRelationshipFigure && firstRelationshipFigure != secondRelationshipFigure)
        {
            relationshipsVec.push_back(new Relationship(firstRelationshipFigure, secondRelationshipFigure));
            firstRelationshipFigure = nullptr;
            isDrawRelationshipOption = false;
            delete  newRelationship;
            newRelationship = nullptr;
            repaint();
        }
        else if (firstRelationshipFigure == secondRelationshipFigure)
        {
            firstRelationshipFigure = nullptr;
            secondRelationshipFigure = nullptr;
        }
    }
}

void Canvas::beginDrawFigure(QPoint pos)
{
    startPoint = pos;
    endPoint = startPoint;
    isDrawing = true;

    switch(ActiveFigure)
    {
        case FigureRectangle:
        {           
            newFigure = new Rectangle(startPoint, endPoint);
            figuresVec.push_back(newFigure);

            break;
        }
        case FigureTriangle:
        {            
            newFigure = new Triangle(startPoint, endPoint);
            figuresVec.push_back(newFigure);

            break;
        }
        case FigureEllipse:
        {            
            newFigure = new Ellipse(startPoint ,endPoint);
            figuresVec.push_back(newFigure);

            break;
        }
    }
}

void Canvas::cancelOperation()
{
    if (isDrawing)
    {
        isDrawing = false;
        deleteFigure(newFigure);
        newFigure = nullptr;
        repaint();
    }
    else if (beingMovedFigure)
    {
        setCursor(Qt::ArrowCursor);

        beingMovedFigure->setColor(Qt::black);
        beingMovedFigure = nullptr;

        repaint();
    }
    else if (isDrawRelationshipOption)
    {
        firstRelationshipFigure = nullptr;
        isDrawRelationshipOption = false;
        newRelationship = nullptr;

        repaint();
    }
}

Figure* Canvas::getFigureInPosition(QPoint pos)
{
    for(Figure* fig : figuresVec)
    {
        QRect rect = fig->getBoundingArea();
        if(rect.contains(pos))
            return fig;
    }

    return nullptr;
}

void Canvas::deleteFigure(Figure* beingDeleteFigure)
{
    for (auto it = figuresVec.cbegin(); it != figuresVec.cend(); ++it)
    {
        Figure* fig = *it;
        if(fig == beingDeleteFigure)
        {
            for (auto iter = relationshipsVec.cbegin(); iter != relationshipsVec.cend(); )
            {
                Relationship* relationship = *iter;
                if(relationship->firstFigure == beingDeleteFigure || relationship->secondFigure == beingDeleteFigure)
                {
                    delete *iter;
                    iter = relationshipsVec.erase(iter);
                    continue;
                }

                ++iter;
            }

            delete fig;
            figuresVec.erase(it);
            break;
        }
    }
}
