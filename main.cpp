#include "mainwindow.h"

#include <QApplication>

#include <chrono>

#include "graph.h"

char* getCmdOption(char ** begin, char ** end, const std::string & option)
{
    char ** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return 0;
}

bool cmdOptionExists(char** begin, char** end, const std::string& option)
{
    return std::find(begin, end, option) != end;
}

int main(int argc, char *argv[])
{
    if(cmdOptionExists(argv, argv+argc, "--help"))
    {
        std::cout << "===   HELP   ===" << std::endl;
        std::cout << "Command :" << std::endl;
        std::cout << " --help        : Help" << std::endl;
        std::cout << " --start       : Starting Vertex" << std::endl;
        std::cout << " --end         : Ending help" << std::endl;
        std::cout << " --algorithm   : bfs / dijkstra / astar" << std::endl;
        std::cout << " --file        : File path" << std::endl;
        std::cout << "=== END  HELP ===" << std::endl;
        return 0;
    }

    string filename = getCmdOption(argv, argv + argc, "--file");

    auto start = std::chrono::steady_clock::now();
    Graph graph(filename);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    cout << "CACHE - elapsed time: " << elapsed_seconds.count() << " sec" << endl << endl;

    int vstart = stod(getCmdOption(argv, argv + argc, "--start"));
    int vend = stod(getCmdOption(argv, argv + argc, "--end"));
    string algo = getCmdOption(argv, argv + argc, "--algorithm");

    if ( (algo == "bfs") || (algo == "dijkstra") || (algo == "astar") ) {
        std::cout << "Algorithm " << algo << " starts" <<  std::endl;
    }
    else {
        std::cout << "Algorithm not found, exit error" << std::endl;
        return 1;
    }

    list<int> ve;
    start = std::chrono::steady_clock::now();
    if (algo == "bfs") {
        ve = graph.BFS(vstart, vend);
    }
    if (algo == "dijkstra") {
        ve = graph.Dijkstra(vstart, vend);
    }
    if (algo == "astar") {
        ve = graph.Astar(vstart, vend);
    }
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    std::cout << algo << " - elapsed time: " << elapsed_seconds.count() << " sec" << std::endl << std::endl;

    // QT display
    start = std::chrono::steady_clock::now();
    QApplication a(argc, argv);
    MainWindow w(graph, ve);
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end-start;
    cout << "PAINT - elapsed time: " << elapsed_seconds.count() << " sec" << endl;
    w.show();
    return a.exec();

/*
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

    // third BFS test
    start = std::chrono::steady_clock::now();
    list<int> ve = graph.BFS(86771, 110636);
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    std::cout << "BFS - elapsed time: " << elapsed_seconds.count() << " sec" << std::endl << std::endl;

    // Dijkstra
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

    // Astar
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
*/

}
