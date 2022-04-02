#include "mainwindow.h"
#include "view.h"

#include <QHBoxLayout>
#include <QSplitter>

MainWindow::MainWindow(Graph g, QWidget *parent)
    : QWidget(parent), scene(new QGraphicsScene(this))
    , h1Splitter(new QSplitter(this)), h2Splitter(new QSplitter(this))
{
    populateScene(g);   // read graph + display

    QSplitter *vSplitter = new QSplitter;
    vSplitter->setOrientation(Qt::Vertical);
    vSplitter->addWidget(h1Splitter);
    vSplitter->addWidget(h2Splitter);

    View *view = new View("Map");
    view->view()->setScene(scene);
    h1Splitter->addWidget(view);

    //view = new View("Top right view");
    //view->view()->setScene(scene);
    //h1Splitter->addWidget(view);

    //view = new View("Bottom left view");
    //view->view()->setScene(scene);
    //h2Splitter->addWidget(view);

    //view = new View("Bottom right view");
    //view->view()->setScene(scene);
    //h2Splitter->addWidget(view);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(vSplitter);
    setLayout(layout);

    setWindowTitle(tr("MapPathFinder"));
}

void MainWindow::populateScene(Graph g)
{
    //QColor color(image.pixel(int(image.width() * x), int(image.height() * y)));
    //QGraphicsItem *item = new Chip(color, xx, yy);
    //item->setPos(QPointF(i, j));
    //scene->addItem(item);

    QPainter painter(this);

    vector<int> VIdList;
    VIdList = g.getVertexIdList();
    int cpte=0;
    Vertex ve, vto;
    //double xmap, ymap;
    //int height=10000000, width=10000000;
    for (int i = 0; i < int(VIdList.size()); i++) {
    //for (int i = 0; i < 15; i++) {
        ve = g.getVertexByID(VIdList.at(i));
        //QRectF r(ve.getX(),ve.getY(),0.00001,0.00001);
        //scene->addRect(r);
        list <Edge> EdgeList = ve.getEdgeList();
        for (auto it = EdgeList.begin(); it != EdgeList.end(); it++) {
            vto = g.getVertexByID(it->getDestinationVertexID());
            //QLineF line_temp(ve.getX(),ve.getY(),vto.getX(),vto.getY());
            //scene->addLine(line_temp);

            // width is map width
            //x = fmod((width*(180+lon)/360), (width +(width/2)));
            //xmap = fmod((width*ve.getX()), (width +(width/2)));

            // height and width are map height and width
            //double PI = 3.14159265359;
            //double latRad = lat*PI/180;
            // get y value
            //double mercN = log(tan((PI/4)+(latRad/2)));
            //y = (height/2)-(width*mercN/(2*PI));
            //ymap = (height/2)-(width*vto.getX());

            //, int height=10000000, int width=10000000

            scene->addLine(QLineF(ve.getX(),ve.getY(),vto.getX(),vto.getY()));
            cpte++;
        }
    }
    cout << cpte << endl;
    //painter.drawPoint(15,15);
}

