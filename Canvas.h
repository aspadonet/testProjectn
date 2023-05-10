#ifndef CANVAS_H
#define CANVAS_H

#include "Figure.h"
#include "Relationship.h"
#include <QWidget>
#include <vector>

class Canvas : public QWidget
{
    enum DrawOption
    {
        DrawFigureOption,
        DrawRelationshipOption,
        MoveFigureOption,
        DeleteFigureOption,
    };

public:
    Canvas(QWidget* parent);
    ~Canvas();

    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

    void initialOptionDrawFigure(FigureType figure);
    void initialOptionFigureMove();
    void initialOptionDrawRelationship();
    void initialOptionDeleteFigure();

    std::vector<Figure*>& getVectorFigure();
    void setVectorFigure(const std::vector<Figure*>& figuresVec);

    std::vector<Relationship*>& getVectorRelationship();
    void setVectorRelationship(const std::vector<Relationship*>& RelationshipsVec);

private:
    void beginDrawFigure(QPoint position);
    void beginDeleteFigure(QPoint position);
    void beginMoveFigure(QPoint position);
    void beginDrawRelationship(QPoint position);

    void cancelOperation();

    Figure* getFigureInPosition(QPoint position);
    void deleteFigure(Figure* fig);

    FigureType ActiveFigure = FigureRectangle;
    DrawOption drawOption = DrawFigureOption;

    Figure* beingMovedFigure = nullptr;
    Figure* firstRelationshipFigure = nullptr;

    std::vector<Figure*> figuresVec;
    std::vector<Relationship*> relationshipsVec;

    Figure* newFigure = nullptr;
    Relationship* newRelationship = nullptr;

    QPoint startPoint;
    QPoint endPoint;

    int shapeType = 0;
    bool isDrawing = false;
    bool isDrawRelationshipOption = false;
};

#endif // CANVAS_H
