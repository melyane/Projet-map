
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "graph.h"

QT_BEGIN_NAMESPACE
class QGraphicsScene;
class QSplitter;
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(Graph g, QWidget *parent = nullptr);

private:
    void setupMatrix();
    void populateScene(Graph g);

    QGraphicsScene *scene;
    QSplitter *h1Splitter;
    QSplitter *h2Splitter;
};

#endif // MAINWINDOW_H
