#include "mainwindow.h"

#include <QApplication>

#include "graph.h"

int main(int argc, char *argv[])
{
    // file name is argv[2]
    // create a graph object from given file
    //Graph graph(argv[2]);
    Graph graph("../MapPathFinder/graph_dc_area.2022-03-11.txt");
    graph.printGraph();

    // QT display
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
