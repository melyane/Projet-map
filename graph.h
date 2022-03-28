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

    list < Edge > edgeList;

    // constructor
    Vertex() {
        Vertex_id = 0;
        longitude = 0;
        latitude = 0;
        x = 0;
        y = 0;
    }
    Vertex(int id, double lo, double la, double xd=0, double yd=0) {
        Vertex_id = id;
        longitude = lo;
        latitude = la;
        x = xd;
        y = yd;
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
        cout << "[";
        for (auto it = edgeList.begin(); it != edgeList.end(); it++) {
            cout << it->getDestinationVertexID() << " - "
                 << it->getName() << "(" << it->getWeight() << "("
                 << it->getExra0() << ", " << it->getExtra1() << ") --> ";
        }
        cout << "]";
        cout << endl;
    }

    void updateVertexName(double lo, double la, double xd=0, double yd=0) {
        longitude = lo;
        latitude = la;
        x = xd;
        y = yd;
        cout << "Vertex Name Updated Successfully";
    }

};

class Graph {

    vector < Vertex > vertices;

    public:

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
            cout << "New Vertex Added Successfully" << endl;
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
        cout << "Vertex(State) Updated Successfully " << endl;
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
                cout << "Edge between " << fromVertex << " and " << toVertex << " added Successfully" << endl;
            }
        } else {
            cout << "Invalid Vertex ID entered.";
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
            cout << "Edge Weight Updated Successfully " << endl;
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
            cout << "Edge Between " << fromVertex << " and " << toVertex << " Deleted Successfully." << endl;
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
        cout << "Vertex Deleted Successfully" << endl;
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

    Graph(string fname) {
        string line, word;
        vector<string> row;
        ifstream name;
        name.open(fname);
        if (!name.is_open()) {
            cout << "Error : cannot open the file " << fname << endl;
            exit(EXIT_FAILURE);
        }
        int id1, id2 ;
        double lo, la, xd, yd, w ;
        string n, e0, e1;
        while (true) {
            // read new line
            getline(name, line);
            if (name.eof()) break;
            cout << "DEBUG_0 : " << line << endl;
            // clean buffer
            row.clear();
            // new vertex data
            if (line.front()=='V') {
                stringstream str(line);
                while(getline(str, word, ',')) {
                    row.push_back(word);
                }
                id1 = atoi(row[1].c_str());
                lo = atoi(row[1].c_str());
                la = atof(row[2].c_str());
                if (row[3] == "") { xd = 0; } else { xd = atof(row[3].c_str()); }
                if (row[4] == "") { yd = 0; } else { yd = atof(row[4].c_str()); }
                // add new vertex in graph
                Vertex e(id1, lo, la, xd, yd);
                addVertex(e);
            }
            // new edge data
            if (line.front()=='E') {
                stringstream str(line);
                while(getline(str, word, ',')) {
                    row.push_back(word);
                }
                id1 = atoi(row[1].c_str()) ;
                id2 = atoi(row[2].c_str()) ;
                w = atof(row[3].c_str()) ;
                n = row[4] ;
                e0 = row[5] ;
                e1 = row[6] ;
                // add new edge in graph
                addEdgeByID(id1, id2, w, n, e0, e1);
            }
        }
    }

};


#endif // GRAPH_H
