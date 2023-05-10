#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QToolBar>
#include <QMessageBox>
#include <QPainter>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include "Rectangle.h"
#include "Ellipse.h"
#include "Triangle.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QToolBar* toolbar = new QToolBar(this);

    toolbar->addAction(QIcon(":/res/rectangle.svg"), tr("Rectangle"), this, &MainWindow::addRectangle);
    toolbar->addAction(QIcon(":/res/triangle.svg"), tr("Triangle"), this, &MainWindow::addTriangle);
    toolbar->addAction(QIcon(":/res/ellipse.svg"), tr("Ellipse"), this, &MainWindow::addEllipse);
    toolbar->addSeparator();
    toolbar->addAction(QIcon(":/res/ralationship.svg"), tr("Ralationship"), this, &MainWindow::addRalationship);
    toolbar->addSeparator();
    toolbar->addAction(QIcon(":/res/hand.svg"), tr("Hand"), this, &MainWindow::Hand);
    toolbar->addAction(QIcon(":/res/dustbin.svg"), tr("dustbin"), this, &MainWindow::Dustbin);
    toolbar->addSeparator();
    toolbar->addAction(QIcon(":/res/readFromFile.svg"), tr("ReadFromFile"), this, &MainWindow::readFromFile);
    toolbar->addAction(QIcon(":/res/saveToFile.svg"), tr("SaveToFile"), this, &MainWindow::saveToFile);

    addToolBar(toolbar);

    canvas = new Canvas(this);
    setCentralWidget(canvas);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addRectangle()
{
    canvas->initialOptionDrawFigure(FigureRectangle);
}

void MainWindow::addTriangle()
{
    canvas->initialOptionDrawFigure(FigureTriangle);
}

void MainWindow::addEllipse()
{
    canvas->initialOptionDrawFigure(FigureEllipse);
}

void MainWindow::addRalationship()
{
    canvas->initialOptionDrawRelationship();
}

void MainWindow::Hand()
{
    canvas->initialOptionFigureMove();
}

void MainWindow::Dustbin()
{
    canvas->initialOptionDeleteFigure();
}

void MainWindow::readFromFile()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open File");

    QFile file(filename);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::critical(this, "program", "Can't open file");
        return;
    }

    std::vector<Figure*> figuresVec;
    std::map<int, Figure*> figuresMap;
    std::vector<Relationship*> relationshipVec;

    QTextStream in(&file);
    QString line = in.readLine();
    while (!line.isNull())
    {
        QStringList parts = line.split("\t");
        QString figureType = parts[0];
        if("Relationship" == figureType)
        {
            QStringList parts = line.split("\t");
            int firstFigureId = parts[1].toInt();
            int secondFigureId = parts[2].toInt();

            Figure* fTemp = figuresMap[firstFigureId];
            Figure* sTemp = figuresMap[secondFigureId];

            if(fTemp != nullptr && sTemp != nullptr)
                relationshipVec.push_back(new Relationship( fTemp, sTemp ));
        }
        else
        {
            QStringList parts = line.split("\t");
            QString shape = parts[0];
            int id = parts[1].toInt();
            int xStart = parts[2].toInt();
            int yStart = parts[3].toInt();
            int xEnd = parts[4].toInt();
            int yEnd = parts[5].toInt();

            QPoint start(xStart, yStart);
            QPoint end(xEnd, yEnd);

            if("Rectangle" == figureType){
                figuresVec.push_back(new Rectangle(start, end, id));
            }
            else if("Triangle" == figureType){
                figuresVec.push_back(new Triangle(start, end, id));
            }
            else if("Ellipse" == figureType){
                figuresVec.push_back(new Ellipse(start, end, id));
            }
            figuresMap[figuresVec.back()->getId()] = figuresVec.back();
        }

        line = in.readLine();
    }

    canvas->setVectorFigure(figuresVec);
    canvas->setVectorRelationship(relationshipVec);

    file.close();
}

void MainWindow::saveToFile()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save File");

    QFile file(filename);
    file.open(QIODevice::WriteOnly| QIODevice::Text);

    QTextStream out(&file);

    for(Figure* fig : canvas->getVectorFigure())
        out << fig->GetName() << "\t"
            << fig->getId() << "\t"
            << fig->getStartPoint().x() << "\t"
            << fig->getStartPoint().y()<< "\t"
            << fig->getEndPoint().x() << "\t"
            << fig->getEndPoint().y() << "\n";

    for(Relationship* relationship : canvas->getVectorRelationship())
        out << "Relationship" << "\t"
            << relationship->firstFigure->getId() << "\t"
            << relationship->secondFigure->getId() << "\n";

    file.close();
}
