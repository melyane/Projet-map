#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <fstream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <utility>

using namespace std;

class Edge;
class Vertex;

class Edge {
    public:
    int DestinationVertexID;
    double weight;
    string name;
    string extra0;
    string extra1;

    // Constructor
    Edge() {}
    Edge(int destVID, double w, string n="", string e0="", string e1="") {
        DestinationVertexID = destVID;
        weight = w;
        name = n;
        extra0 = e0;
        extra1 = e1;
    }

    // set functions
    void setEdgeValues(int destVID, double w, string n="", string e0="", string e1="") {
        DestinationVertexID = destVID;
        weight = w;
        name = n;
        extra0 = e0;
        extra1 = e1;
    }

    void setWeight(double w) {
        weight = w;
    }
    void setName(string n) {
        name = n;
    }
    void setExtra0(string e0) {
        extra0 = e0;
    }
    void setExtra1(string e1) {
        extra1 = e1;
    }

    // get functions
    int getDestinationVertexID() {
        return DestinationVertexID;
    }
    double getWeight() {
        return weight;
    }
    string getName() {
        return name;
    }
    string getExra0() {
        return extra0;
    }
    string getExtra1() {
        return extra1;
    }
};

class Vertex {
    public:
    int Vertex_id;
    double longitude;
    double latitude;
    double x;
    double y;
    double weight;

    list < Edge > edgeList;

    // constructor
    Vertex() {
        Vertex_id = 0;
        longitude = 0;
        latitude = 0;
        x = 0;
        y = 0;
        weight = 0;
    }
    Vertex(int id, double lo, double la, double xd=0, double yd=0) {
        Vertex_id = id;
        longitude = lo;
        latitude = la;
        x = xd;
        y = yd;
        weight = 0;
    }

    // get functions
    int getID() {
        return Vertex_id;
    }
    double getLongitude() {
        return longitude;
    }
    double getLatitude() {
        return latitude;
    }
    double getX() {
        return x;
    }
    double getY() {
        return y;
    }
    double getWeight() {
        return weight;
    }


    // set functions
    void setID(int id) {
        Vertex_id = id;
    }
    void setLongitude(double lo) {
        longitude = lo;
    }
    void setLatitude(double la) {
        latitude = la;
    }
    void setX(double xd) {
        x = xd;
    }
    void setY(double yd) {
        y = yd;
    }
    void setWeight(double w) {
        weight = w;
    }

    void setXMerc(double lon) {
        x = 6378137*cos(38.99971*M_PI/180)*(lon+77.13325)*M_PI/180;
    }
    void setYMerc(double lat) {
        y = -6378137*log(tan((lat-38.99971)*M_PI/360+M_PI/4));
    }

    // edge functions
    list < Edge > getEdgeList() {
        return edgeList;
    }

//  void addEdgeToEdgelist(int toVertexID, int weight)
//  {
//	  	Edge e(toVertexID,weight);
//		edgeList.push_back(e);
//		cout<<"Edge between "<<Vertex_id<<" and "<<toVertexID<<" added Successfully"<<endl;
//  }

    void printEdgeList() {
        cout << "[ ";
        for (auto it = edgeList.begin(); it != edgeList.end(); it++) {
            cout << it->getDestinationVertexID() << " ";
                 // << it->getName() << " (" << it->getWeight() << ") --> ";
        }
        cout << "]";
        cout << endl;
    }

    double getWeightbyId(int id) {
        for (auto it = edgeList.begin(); it != edgeList.end(); it++) {
            if (it->getDestinationVertexID() == id) {
                return it->getWeight();
            }
        }
        return 0;
    }

    list<int> getEdgesIdList(list<int> &le) {
        le.clear();
        for (auto it = edgeList.begin(); it != edgeList.end(); it++) {
            le.push_back(it->getDestinationVertexID());
        }
        return le;
    }

    void updateVertexName(double lo, double la, double xd=0, double yd=0) {
        longitude = lo;
        latitude = la;
        x = xd;
        y = yd;
        //cout << "Vertex Name Updated Successfully";
    }


};



class Graph {

    vector < Vertex > vertices;

    protected:

    int readVertex(string fname) {
        string line, word;
        vector<string> row;
        ifstream name;
        name.open(fname);
        if (!name.is_open()) {
            cout << "Error : cannot open the file " << fname << endl;
            exit(EXIT_FAILURE);
        }
        int id1, cpt=0 ;
        double lo, la ;
        string n, e0, e1;
        while (getline(name, line)) {
            // clean buffer
            row.clear();
            // new vertex data
            if (line.front()=='V') {
                stringstream str(line);
                while(getline(str, word, ',')) {
                    row.push_back(word);
                }
                row.push_back("");
                id1 = stoi(row[1]);
                lo = stod(row[2]);
                la = stod(row[3]);
                // add new vertex in graph
                //cout << "DEBUG_1 : V," << id1 << "," << lo << "," << la << "," << endl;
                Vertex e(id1, lo, la);
                e.setXMerc(lo);
                e.setYMerc(la);
                //cout << "x=" << e.getX() << " y=" << e.getY() << endl;
                addVertex(e);
                cpt++;
            }
        }
       return cpt;
    }

    int readEdge(string fname) {
        string line, word;
        vector<string> row;
        ifstream name;
        name.open(fname);
        if (!name.is_open()) {
            cout << "Error : cannot open the file " << fname << endl;
            exit(EXIT_FAILURE);
        }
        int cpt=0;
        //int id1, id2 ;
        //double w, x1, x2, y1, y2 ;
        //double w;
        //string n, e0, e1;
        string n;
        while (getline(name, line)) {
            // clean buffer
            row.clear();
            // new edge data
            if (line.front()=='E') {
                stringstream str(line);
                while(getline(str, word, ',')) {
                    row.push_back(word);
                }
                //row.push_back("");
                //id1 = stoi(row[1]) ;
                //id2 = stoi(row[2]) ;
                //w = stod(row[3]) ;
                //n = row[4] ;
                //e0 = row[5] ;
                //e1 = row[6] ;
                // add new edge in graph
                //cout << "DEBUG_1 : E," << id1 << "," << id2 << "," << w << "," << n << "," << e0 << "," << e1 << endl;
                //x1 = getVertexByID(id1).getX();
                //y1 = getVertexByID(id1).getY();
                //x2 = getVertexByID(id2).getX();
                //y2 = getVertexByID(id2).getY();
                //w  = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
                //addEdgeByID(id1, id2, w, n, e0, e1);
                //addEdgeByID(id1, id2, w, n);
                addEdgeByID(stoi(row[1]), stoi(row[2]), stod(row[3]), row[4]);
                cpt++;
            }
        }
       return cpt;
    }

    void set_weight_merc_on_edges() {
        vector<int> V1list = getVertexIdList();
        list<Edge> le;
        double x1, x2, y1, y2;
        int v2;
        for (auto v1 = std::begin(V1list); v1 != std::end(V1list); ++v1) {
            le = getVertexByID(*v1).getEdgeList();
            for (auto ite = std::begin(le); ite != std::end(le); ++ite) {
                v2 = ite->getDestinationVertexID();
                x1 = getVertexByID(*v1).getX();
                y1 = getVertexByID(*v1).getY();
                x2 = getVertexByID(v2).getX();
                y2 = getVertexByID(v2).getX();
                ite->setWeight(sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
            }
        }
    }

    void set_infinite_weight(int vstart) {
        Vertex temp;
        vector<int> V1list = getVertexIdList();
        for (auto v1 = std::begin(V1list); v1 != std::end(V1list); ++v1) {
            temp = vertices.at(*v1);
            temp.setWeight(99999999);
        }
        temp = vertices.at(vstart);
        temp.setWeight(0);
    }

    public:

    Graph(string fname) {
        int cptV, cptE;
        cptV = readVertex(fname);
        cptE = readEdge(fname);
        cout << "nb de Vertex : " << cptV << " et nb de Edges : " << cptE << endl;
    }

    vector<int> getVertexIdList() {
        vector<int> Vlist;
        for (int i = 0; i < int(vertices.size()); i++) {
            Vlist.push_back(vertices.at(i).getID());
        }
        return Vlist;
    }

    bool checkIfVertexExistByID(int vid) {
        bool flag = false;
        for (int i = 0; i < int(vertices.size()); i++) {
            if (vertices.at(i).getID() == vid) {
                return true;
            }
        }
        return flag;
    }

    void addVertex(Vertex newVertex) {
        bool check = checkIfVertexExistByID(newVertex.getID());
        if (check == true) {
            cout << "Vertex with this ID already exist" << endl;
        } else {
            vertices.push_back(newVertex);
            //cout << "New Vertex Added Successfully" << endl;
        }
    }

    Vertex getVertexByID(int vid) {
        Vertex temp;
        for (int i = 0; i < int(vertices.size()); i++) {
            temp = vertices.at(i);
            if (temp.getID() == vid) {
                return temp;
            }
        }
        return temp;
    }

    bool checkIfEdgeExistByID(int fromVertex, int toVertex) {
        Vertex v = getVertexByID(fromVertex);
        list < Edge > e;
        e = v.getEdgeList();
        bool flag = false;
        for (auto it = e.begin(); it != e.end(); it++) {
            if (it -> getDestinationVertexID() == toVertex) {
                flag = true;
                return flag;
                break;
            }
        }
        return flag;
    }

    void updateWeightVertex(int oldVID, double w) {
        bool check = checkIfVertexExistByID(oldVID);
        if (check == true) {
            for (int i = 0; i < int(vertices.size()); i++) {
                if (vertices.at(i).getID() == oldVID) {
                    vertices.at(i).setWeight(w);
                    break;
                }
            }
        //cout << "Vertex(State) Updated Successfully " << endl;
        }
    }

    void updateVertex(int oldVID, double lo, double la, double xd=0, double yd=0) {
        bool check = checkIfVertexExistByID(oldVID);
        if (check == true) {
            for (int i = 0; i < int(vertices.size()); i++) {
                if (vertices.at(i).getID() == oldVID) {
                    vertices.at(i).setLongitude(lo);
                    vertices.at(i).setLatitude(la);
                    vertices.at(i).setX(xd);
                    vertices.at(i).setY(yd);
                    break;
                }
            }
        //cout << "Vertex(State) Updated Successfully " << endl;
        }
    }

    void addEdgeByID(int fromVertex, int toVertex, double weight, string name, string extra0="", string extra1="") {
        bool check1 = checkIfVertexExistByID(fromVertex);
        bool check2 = checkIfVertexExistByID(toVertex);
        bool check3 = checkIfEdgeExistByID(fromVertex, toVertex);
        if ((check1 && check2 == true)) {
            if (check3 == true) {
                cout << "Edge between id" << fromVertex
                     << "(" << getVertexByID(fromVertex).getLongitude() << "," << getVertexByID(fromVertex).getLatitude() << ") and id" << toVertex
                     << "(" << getVertexByID(toVertex).getLongitude() << "," << getVertexByID(toVertex).getLatitude() << ") Already Exists" << endl;
            } else {
                for (int i = 0; i < int(vertices.size()); i++) {
                    if (vertices.at(i).getID() == fromVertex) {
                        Edge e(toVertex, weight, name, extra0, extra1);
                        vertices.at(i).edgeList.push_back(e);
                    }
                }
                //cout << "Edge between " << fromVertex << " and " << toVertex << " added Successfully" << endl;
            }
        } else {
            cout << "Invalid Vertex ID entered." << endl;
            exit(1);
        }
    }

    void updateEdgeByID(int fromVertex, int toVertex, double newWeight, string newName, string newExtra0="", string newExtra1="") {
        bool check = checkIfEdgeExistByID(fromVertex, toVertex);
        if (check == true) {
            for (int i = 0; i < int(vertices.size()); i++) {
                if (vertices.at(i).getID() == fromVertex) {
                    for (auto it = vertices.at(i).edgeList.begin(); it != vertices.at(i).edgeList.end(); it++) {
                        if (it -> getDestinationVertexID() == toVertex) {
                            it -> setWeight(newWeight);
                            it -> setName(newName);
                            it -> setExtra0(newExtra0);
                            it -> setExtra1(newExtra1);
                            break;
                        }
                    }
                }
            }
            //cout << "Edge Weight Updated Successfully " << endl;
        } else {
            cout << "Edge between id" << fromVertex << " and id" << toVertex << " DOES NOT Exist" << endl;
        }
    }

    void deleteEdgeByID(int fromVertex, int toVertex) {
        bool check = checkIfEdgeExistByID(fromVertex, toVertex);
        if (check == true) {
            for (int i = 0; i < int(vertices.size()); i++) {
                if (vertices.at(i).getID() == fromVertex) {
                    for (auto it = vertices.at(i).edgeList.begin(); it != vertices.at(i).edgeList.end(); it++) {
                        if (it -> getDestinationVertexID() == toVertex) {
                            vertices.at(i).edgeList.erase(it);
                            break;
                        }
                    }
                }
            }
            //cout << "Edge Between " << fromVertex << " and " << toVertex << " Deleted Successfully." << endl;
        } else {
            cout << "Edge between id" << fromVertex << " and id" << toVertex << " DOES NOT Exist" << endl;
        }
    }

    void deleteVertexByID(int vid) {
        int vIndex = 0;
        for (int i = 0; i < int(vertices.size()); i++) {
            if (vertices.at(i).getID() == vid) {
                vIndex = i;
            }
        }
        for (int i = 0; i < int(vertices.size()); i++) {
            for (auto it = vertices.at(i).edgeList.begin(); it != vertices.at(i).edgeList.end(); it++) {
                if (it -> getDestinationVertexID() == vid) {
                    vertices.at(i).edgeList.erase(it);
                    break;
                }
            }
        }
        vertices.erase(vertices.begin() + vIndex);
        //cout << "Vertex Deleted Successfully" << endl;
    }

    void getAllNeigborsByID(int vid) {
        cout << " id(" << getVertexByID(vid).getID() << ") --> ";
        for (int i = 0; i < int(vertices.size()); i++) {
            if (vertices.at(i).getID() == vid) {
            cout << "[";
                for (auto it = vertices.at(i).edgeList.begin(); it != vertices.at(i).edgeList.end(); it++) {
                    cout << it -> getDestinationVertexID() << "(" << it -> getWeight() << ") --> ";
                }
                cout << "]";
            }
        }
    }

    void printGraph() {
        for (int i = 0; i < int(vertices.size()); i++) {
            Vertex temp;
            temp = vertices.at(i);
            cout << " id(" << temp.getID() << ") --> ";
            temp.printEdgeList();
        }
    }

    void analyze(list<pair<int,int>> &p, list<int> &fp) {
        fp.clear();
        pair<int,int> elem = p.front();
        int previous = elem.first;
        fp.push_front(elem.second);
        for (auto it = std::begin(p); it != std::end(p); ++it) {
            elem = *it;
            if (previous == elem.second) {
                fp.push_front(elem.second);
                previous = elem.first;
            }
        }
    }

    void create_log (int cpt, list<int> &le) {
        double length = 0.0;
        int nb_v = 1;
        cout << "Total visited vertex = " << cpt << endl;
        cout << "Total vertex on path from start to end = " << le.size() << endl;
        for (auto it = std::begin(le); it != std::end(le); ++it) {
            int id = *it;
            cout << setprecision(2) << fixed << "Vertex [" << setw(4) << nb_v << "] = " << setw(8) << id << ", length = " << setw(8) << length << endl;
            if (it != --std::end(le)) {
                int id2 = *(++it); --it;
                length += getVertexByID(id).getWeightbyId(id2);
            }
            nb_v+=1;
        }
    }

    // BFS algorithm
    list<int> BFS(int vstart, int vstop) {
        // initialize
        list<int> active_queue, closed_set, temp_list, final_path;
        list<pair<int,int>> path;
        path.push_front(pair<int,int>(-1,vstart));
        int cpt=1;
        int vcurrent, vnext;
        // ID of the start vertex
        active_queue.push_back(vstart);
        do {
            vcurrent = active_queue.front();
            active_queue.pop_front();
            closed_set.push_front(vcurrent);
            // list of edges in current vertex
            getVertexByID(vcurrent).getEdgesIdList(temp_list);
            for (auto it = std::begin(temp_list); it != std::end(temp_list); ++it) {
                vnext = *it;
                if (vnext == vstop) {
                    std::cout << "=== FINAL PATH found ===" << std::endl;
                    //std::cout << "first elem : " << vstart << " and last elem : " << vstop << std::endl;
                    path.push_front(pair<int,int>(vcurrent,vnext));
                    analyze(path, final_path);
                    create_log(cpt, final_path);
                    return final_path;
                }
                // if exists in closed_set
                if ((std::find(closed_set.begin(), closed_set.end(), vnext) != closed_set.end())) {
                    continue;
                }
                // if does not exist in active_queue
                if ((std::find(active_queue.begin(), active_queue.end(), vnext) == active_queue.end())) {
                    active_queue.push_back(vnext);
                    path.push_front(pair<int,int>(vcurrent,vnext));
                    ++cpt;
                }
            }
        } while (active_queue.size()!=0);
        create_log(cpt, final_path);
        return final_path;
    }


    // Dijkstra algorithm
    list<int> Dijkstra(int vstart, int vstop) {
        // reset weight values
        set_infinite_weight(vstart);
        // initialize
        list<int> active_queue, closed_set, temp_list, final_path;
        list<pair<int, double>> temp_sort;
        list<pair<int,int>> path;
        path.push_front(pair<int,int>(-1,vstart));
        int cpt=1;
        int vcurrent, vnext;
        // ID of the start vertex
        active_queue.push_back(vstart);
        do {
            vcurrent = active_queue.front();
            active_queue.pop_front();
            closed_set.push_front(vcurrent);
            // list of edges in current vertex
            getVertexByID(vcurrent).getEdgesIdList(temp_list);
            for (auto it = std::begin(temp_list); it != std::end(temp_list); ++it) {
                vnext = *it;
                if (vnext == vstop) {
                    std::cout << "=== FINAL PATH found ===" << std::endl;
                    path.push_front(pair<int,int>(vcurrent,vnext));
                    analyze(path, final_path);
                    create_log(cpt, final_path);
                    return final_path;
                }
                // if exists in closed_set
                if ((std::find(closed_set.begin(), closed_set.end(), vnext) != closed_set.end())) {
                    continue;
                }
                double w = getVertexByID(vcurrent).getWeight() + getVertexByID(vcurrent).getWeightbyId(vnext);
                // if does not exist in active_queue
                if ((std::find(active_queue.begin(), active_queue.end(), vnext) == active_queue.end())) {
                    //getVertexByID(vnext).setWeight(w);
                    updateWeightVertex(vnext, w);
                    active_queue.push_back(vnext);
                    path.push_front(pair<int,int>(vcurrent,vnext));
                    ++cpt;
                }
                else if (w < getVertexByID(vnext).getWeight()) {
                    //getVertexByID(vnext).setWeight(w);
                    updateWeightVertex(vnext, w);
                }
                // the partial sort ensure that the vertex with the smallest w
                // is the first on the active_queue
                temp_sort.clear();
                for (auto its = std::begin(active_queue); its != std::end(active_queue); ++its) {
                    pair<int, double> elem;
                    elem.first = *its;
                    elem.second = getVertexByID(*its).getWeight();
                    temp_sort.push_back(elem);
                }
                temp_sort.sort([](pair<int, double> a, pair<int, double> b)
                {
                    return a.second < b.second;
                });
                active_queue.clear();
                for (auto itt = std::begin(temp_sort); itt != std::end(temp_sort); ++itt) {
                    pair<int,double> p = *itt;
                    active_queue.push_back(p.first);
                }
            }
        } while (active_queue.size()!=0);
        create_log(cpt, final_path);
        return final_path;
    }

};

#endif // GRAPH_H
