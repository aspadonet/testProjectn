#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Canvas.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void addRectangle();
    void addTriangle();
    void addEllipse();
    void addRalationship();
    void Hand();
    void Dustbin();
    void readFromFile();
    void saveToFile();

    Ui::MainWindow *ui;
    Canvas* canvas = nullptr;
    Figure* fig = nullptr;

};
#endif // MAINWINDOW_H
