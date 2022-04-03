#include "mainwindow.h"

#include <QApplication>

#include <chrono>

#include "graph.h"


/*void test_bfs(Graph graph, int vstart, int vstop) {
    list<int> path = graph.BFS(vstart, vstop);
    std::cout << "PathFinder : start " << vstart << " to " << vstop << " with " << path.size() << " vertices" << std::endl;
    std::cout << "PATH : " << std::endl;
    for (int i: path) {
        std::cout << i << " => ";
    }
    std::cout << std::endl;
}*/

int main(int argc, char *argv[])
{
    // cartesian data size
    // lo -77.1166 -76.9105
    // la  38.8135  38.9945

    // file name is argv[2]
    // create a graph object from given file
    auto start = std::chrono::steady_clock::now();
    //Graph graph(argv[2]);
    Graph graph("graph_dc_area.2022-03-11.txt");
    //graph.printGraph();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    cout << "CACHE - elapsed time: " << elapsed_seconds.count() << " sec" << endl << endl;
/*
    // BFS
    // first BFS test
    start = std::chrono::steady_clock::now();
    //test_bfs(graph, 19791, 50179);
    list<int> ve = graph.BFS(19791, 50179);
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    std::cout << "BFS - elapsed time: " << elapsed_seconds.count() << " sec" << std::endl << std::endl;

    // second BFS test
    start = std::chrono::steady_clock::now();
    graph.BFS(73964, 272851);
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    std::cout << "BFS - elapsed time: " << elapsed_seconds.count() << " sec" << std::endl << std::endl;
*/
    // third BFS test
    start = std::chrono::steady_clock::now();
    list<int> ve = graph.BFS(86771, 110636);
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    std::cout << "BFS - elapsed time: " << elapsed_seconds.count() << " sec" << std::endl << std::endl;

/*
    // first Dijkstra test
    start = std::chrono::steady_clock::now();
    graph.Dijkstra(86771, 110636);
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Dijkstra - elapsed time: " << elapsed_seconds.count() << " sec" << std::endl << std::endl;

    // second Dijkstra test
    start = std::chrono::steady_clock::now();
    graph.Dijkstra(73964, 272851);
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Dijkstra - elapsed time: " << elapsed_seconds.count() << " sec" << std::endl << std::endl;
*/

    // first Astar test
    start = std::chrono::steady_clock::now();
    graph.Astar(86771, 110636);
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Astar - elapsed time: " << elapsed_seconds.count() << " sec" << std::endl << std::endl;

    // second Astar test
    start = std::chrono::steady_clock::now();
    graph.Astar(73964, 272851);
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Astar - elapsed time: " << elapsed_seconds.count() << " sec" << std::endl << std::endl;


    // QT display
    start = std::chrono::steady_clock::now();
    QApplication a(argc, argv);
    MainWindow w(graph, ve);
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end-start;
    cout << "PAINT - elapsed time: " << elapsed_seconds.count() << " sec" << endl;
    w.show();
    return a.exec();
}
