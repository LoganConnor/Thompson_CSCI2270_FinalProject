
#ifndef GRAPH_H
#define GRAPH_H
#include<vector>
#include<iostream>

struct vertex;

struct queueVertex{
    int distance; //total path distance
    std::vector<vertex*> path; //path including all the cities on that path
};

struct adjVertex{
    vertex *v; //storing a pointer to the vertex
    int weight; //distance between the two vertices
};

struct vertex{
    std::string name; //city name
    std::vector<adjVertex> adj; //vector of all the city's adjacent cities
    bool visited; //for the findShortestDistance method, whether the city has been checked or not
    int distance; //for the findShortestDistance method, keeps track of the total path distance
    vertex* previous; //for the findShortestDistance method
    bool chargeStation; //whether the city has a charging station or not
};

struct car{
    std::string model; //car model name
    int batRange; //battery range in miles of the car

    car(std::string m, int br){
        model = m;
        batRange = br;
    }
};

class Graph
{
    public:
        Graph();
        ~Graph();
        void addEdge(std::string v1, std::string v2, int weight);
        void addVertex(std::string name);
        void setCharge(std::string name, bool charge);
        void setBatteryRange(int range);
        void displayEdges();
        //void shortestCompleteTraversal(std::string city);    //Currently not functional, commented out until fixed
        void planTrip(std::string v1, std::string v2);       //called to plan the whole trip
        void findShortestPath(std::string v1, std::string v2);      //Find shortest number of nodes between start and end
        void findShortestDistance(std::string v1, std::string v2); //Find the shortest distance in miles between start and end
        int returnShortestDistance(std::string v1, std::string v2);
        void citiesWithinReach(std::string v1, int time);
        int calculateCharge(int dist);
        void printChargingStations(std::vector<vertex*> v, int whichPath);
    protected:
    private:
        std::vector<vertex> vertices;
        int batteryRange;
        bool printed;
        std::vector<vertex> path; //to keep track of shortest distance path without having to print it out
                                    //in case the car cannot make it - need something to check for charging stations

};

#endif // GRAPH_H

