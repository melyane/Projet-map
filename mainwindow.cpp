#include "mainwindow.h"
#include "view.h"

#include <QHBoxLayout>
#include <QSplitter>
#include <QWidget>
#include <QGraphicsScene>

MainWindow::MainWindow(Graph g, QWidget *parent)
    : QWidget(parent), scene(new QGraphicsScene(this))
    , h1Splitter(new QSplitter(this)), h2Splitter(new QSplitter(this))
{
    map(g);   // read graph + display

    QSplitter *vSplitter = new QSplitter;
    vSplitter->setOrientation(Qt::Vertical);
    vSplitter->addWidget(h1Splitter);
    vSplitter->addWidget(h2Splitter);

    View *view = new View("Map");
    view->view()->setScene(scene);
    h1Splitter->addWidget(view);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(vSplitter);
    setLayout(layout);

    setWindowTitle(tr("MapPathFinder"));
}

void MainWindow::map(Graph g) {

    vector<int> VIdList;
    VIdList = g.getVertexIdList();
    int cpte=0;
    Vertex ve, vto;

    QPen pen(qRgb(255, 215, 0));
    pen.setWidth(2);

    scene->setBackgroundBrush(Qt::black);
     for (int i = 0; i < int(VIdList.size()); i++) {
         ve = g.getVertexByID(VIdList.at(i));
         list <Edge> EdgeList = ve.getEdgeList();
         for (auto it = EdgeList.begin(); it != EdgeList.end(); it++) {
             vto = g.getVertexByID(it->getDestinationVertexID());
             scene->addLine(ve.getX(),ve.getY(),vto.getX(),vto.getY(), pen);
             cpte++;
        }
    }
    cout << cpte << endl;
}

