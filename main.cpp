#include "mainwindow.h"

#include <QApplication>

#include <chrono>

#include "graph.h"

int main(int argc, char *argv[])
{
    // cartesian data size
    // lo -77.1166 -76.9105
    // la  38.8135  38.9945

    auto start = std::chrono::steady_clock::now();

    // file name is argv[2]
    // create a graph object from given file
    //Graph graph(argv[2]);
    Graph graph("../MapPathFinder/graph_dc_area.2022-03-11.txt");
    //graph.printGraph();

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    cout << "elapsed time: " << elapsed_seconds.count() << " sec" << endl;

    // QT display
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
