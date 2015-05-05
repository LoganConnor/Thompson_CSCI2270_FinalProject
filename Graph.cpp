#include "Graph.h"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include <cfloat>
#include <climits>

using namespace std;

//Constructor. No initializations required here
Graph::Graph()
{
}


//Destructor
Graph::~Graph()
{
}

/*
Function Prototype:
void Graph::addEdge(string, string, int);

Function Description:
This function creates a connection between two already existing nodes in the graph.
First both sides of the edge (nodes) are found, then each node has its adjacencies
vector modified with a new addition, and the edge is given a weight value.
Note that the second half of the function is commented out because having a square
matrix in the txt file makes it redundant.

Example:
Graph cg;
cg.addEdge("Boulder", "Seattle", 890);

Pre-conditions: Both cities must already exist in the graph, weight must be >0 since it's a distance
Post-conditions: The cities will have a weight, bi-directional connection in the graph
*/
void Graph::addEdge(string v1, string v2, int weight){

    for(int i = 0; i < vertices.size(); i++){ //loop through all vertices looking for starting city
        if(vertices[i].name == v1){
            for(int j = 0; j < vertices.size(); j++){ //loop through and try to find the ending point
                if(vertices[j].name == v2 && i != j){
                    adjVertex av;       //Initialize new adjacent vertex
                    av.v = &vertices[j]; //v is the adjaciency for city that is at vertices[j]
                    av.weight = weight;
                    vertices[i].adj.push_back(av);      //Add av to vertices[i]'s vector of adjacent cities

                    /*another vertex for edge in other direction        //Redundant with square matrix in txt file
                    adjVertex av2;
                    av2.v = &vertices[i];
                    av2.weight = weight;
                    vertices[j].adj.push_back(av2);*/
                }
            }
        }
    }
}

/*
Function Prototype:
void Graph::addVertex(string);

Function Description:
Determines if given city does not exist in vector of city nodes. If not, creates a new node with
the name given as an argument.

Example:
Graph cg;
cg.addVertex("Boulder");

Pre-conditions: City must not exist as a node in vertices yet, else function does nothing.
Post-conditions: Vertices vector, which holds all city nodes, will have another node with name given as argument.
*/
void Graph::addVertex(string n){
    bool found = false;
    for(int i = 0; i < vertices.size(); i++){       //Loop through all cities, determine if node already exists
        if(vertices[i].name == n){
            found = true;
        }
    }
    if(found == false){
        vertex v;       //Create new vertex, set its name, push onto vector holding all city nodes
        v.name = n;
        vertices.push_back(v);

    }
}

/*
Function Prototype:
void Graph::setCharge(string, bool);

Function Description:
Searches through city nodes, if city is found, assigns that city a bool value
for presence of a Tesla Supercharger station

Example:
Graph cg;
cg.setCharge("Boulder", false);

Pre-conditions: City given as argument must exist, bool should already be determined.
Post-conditions:City will now have a set value for presence of a Supercharger.
*/
void Graph::setCharge(string name, bool charge){
    for(int i=0;i<vertices.size();i++){
        if(vertices[i].name == name){           //If city is found, set its chargeStation variable to T/F
            vertices[i].chargeStation = charge;
            break;
        }
    }
}


void Graph::setBatteryRange(int range){
    batteryRange = range;
}


/*
Function Prototype:
void Graph::displayEdges();

Function Description:
Loops through all cities, and at each city loops through the cities in its adjacency vector to get all connected cities.
Prints out each city (node) and all connected cities.

Example:
Graph cg;
cg.displayEdges();

Pre-conditions: Graph must not be empty.
Post-conditions: All cities and each city's connection will print.
*/
void Graph::displayEdges(){
    for(int i = 0; i < vertices.size(); i++){       //Loop through all cities, display its name
        cout<<vertices[i].name<<"-->";
        for(int j = 0; j < vertices[i].adj.size(); j++){    //then display its connected cities
            cout<<vertices[i].adj[j].v->name;
            if(j != vertices[i].adj.size()-1){
                cout<<"***";
            }
        }
        cout<<endl;
    }
}

/*
Function Prototype:
void Graph::planTrip(string, string);

Function Description:
Calls the shortest path and shortest distance functions, feeding both the starting and ending city names
given to it as a parameter.

Example:
Graph cg;
cg.planTrip("Boulder", "Fargo");

Pre-conditions: Starting and ending cities must exist in the graph.
Post-conditions: Shortest path and distance will be calculated, and printed in their respective functions.
*/
void Graph::planTrip(string v1, string v2){
    findShortestPath(v1,v2);
    findShortestDistance(v1,v2);
}

/*
Function Prototype:
int Graph::calculateCharge(int);

Function Description:
Takes in a given distance and determines number of charges needed to cross that distance
using the globally defined car's battery range as given by user inputs.

Example:
Graph cg;
cg.calculateCharge(890);

Pre-conditions: City given as argument must exist, bool should already be determined.
Post-conditions:City will now have a set value for presence of a Supercharger.
*/
int Graph::calculateCharge(int dist){
    return (dist/batteryRange) + 1;     //The +1 accounts for the remainder from the division
}


/*
Function Prototype:
void Graph::findShortestPath(string, string);

Function Description:
Determines the smallest number of nodes in the graph that can be encountered while traversing
from the given starting node to the given ending node. Function first verifies that both
cities are in the graph.

Example:
Graph cg;
cg.findShortestPath("Boulder", "Fargo");

Pre-conditions: Both cities must be in the graph.
Post-conditions: All cities from start to end, as well as a count of encountered cities, will print.
*/
void Graph::findShortestPath(string v1, string v2){
    int i1 = -1;
    int i2 = -1;
    printed = true;
    
    queue<queueVertex> vQueue;      //Queue will hold cities as they are encountered
    vector<vertex*> path;
    queueVertex temp;
    int distance;
    queueVertex qv;
    qv.distance = 0;

    for(int i=0;i<vertices.size();i++){     //Loop through cities to verify that given arguments are valid
        if(vertices[i].name == v1){
            i1 = i;
        }
        if(vertices[i].name == v2){
            i2 = i;
        }
    }

    if(i1 == -1 || i2 == -1){
        cout<<"One or more cities doesn't exist"<<endl;
        printed = false;
        return;
    }

    for(int i=0;i<vertices.size();i++){     //Set all cities as visited=false, necessary for algorithm below or cities will be missed
        vertices[i].visited = false;
    }

    for(int i=0;i<vertices.size();i++){     //Find starting city
        if(vertices[i].name == v1){
            vertices[i].visited = true;
            qv.path.push_back(&vertices[i]);    //Add starting city to path (encountered cities) held by qv
            vQueue.push(qv);        //Push starting city onto queue that holds cities as they are encountered
            break;
        }
    }

    while(!vQueue.empty()){     //When while loop is violated, all cities connected in graph would have to have been visited
        qv = vQueue.front();
        vQueue.pop();
        for(int i=0;i<qv.path.back()->adj.size();i++){      //qv.path.back() holds most recently encountered city
            if(qv.path.back()->adj[i].v->visited == false){     //if a city has not already been encountered
                    path = qv.path;                             //Path is a vector of vertex pointers
                    qv.path.back()->adj[i].v->visited = true;   //Ensure city won't be encountered again
                    distance = qv.distance + 1;
                    path.push_back(qv.path.back()->adj[i].v);   //Add this new city to the path
                    temp.path = path;
                    temp.distance = distance;
                    if(temp.path.back()->name == v2){       //If the city just encountered is the ending city, print everything
                        cout << "The path with the least number of cities on it will take you through these "
                        <<distance+1<< " cities: "<< temp.path[0]->name;
                        for(int j = 1;j<temp.path.size();j++){
                            cout<<", "<<temp.path[j]->name;
                        }
                        cout<<endl;
                        printChargingStations(temp.path,1);
                        return;
                    }
                    else{
                        vQueue.push(temp);      //If the just encountered city is not the ending city, push it onto the queue for examination
                    }
            }
        }
    }
}


/*
Function Prototype:
void Graph::findShortestDistance(string, string);

Function Description:
Determines the smallest distance that can be traveled from a starting node to an ending node, using
the weights of edges between the two nodes. First determines that both cities are in the graph.

Example:
Graph cg;
cg.findShortestDistance("Boulder", "Fargo");

Pre-conditions: Cities given as arguments must exist in graph.
Post-conditions: All cities encountered and the total distance covered will print.
*/
void Graph::findShortestDistance(string v1, string v2){
    int i1 = -1;
    int i2 = -1;

    for(int i=0;i<vertices.size();i++){     //Find indexes of both cities in vector of cities
        if(vertices[i].name == v1){
            i1 = i;
        }
        if(vertices[i].name == v2){
            i2 = i;
        }
    }

    if(i1 == -1 || i2 == -1){
        if (printed == true)
            cout<<"One or more cities doesn't exist"<<endl;
        return;
    }

    vector<vertex*> solved;
    vector<vertex*> finalPath;
    vertex* destPtr;
    int minDistance = INT_MAX;

    for(int i = 0; i < vertices.size(); i++){       //Setting all cities as not visited ensures they won't be missed during algorithm execution
        vertices[i].visited = false;
        vertices[i].previous = NULL;                //Previous should be NULL until start moving through graph and solving nodes
        vertices[i].distance = INT_MAX;             //Guaranteed to be larger than whatever valid distance is calculated during algorithm

        if(vertices[i].name == v1){
            vertices[i].visited = true;
            vertices[i].distance = 0;
            solved.push_back(&vertices[i]);     //Find starting city, push it into vector containing "solved" nodes
        }                                           //where solved means distance to it has been found

        if(vertices[i].name == v2){
            destPtr = &vertices[i];
        }
    }
    vertex* minV;
    vertex* minU;
    while(destPtr->visited == false){
        minDistance = INT_MAX;
        for(int i = 0; i < solved.size(); i++){     //Loop through nodes already solved and take each one, then look at its adjacencies
            vertex* ptrU = solved[i];
            for(int j = 0; j < ptrU->adj.size(); j++){
                vertex* ptrV = ptrU->adj[j].v;              //Take each adjacent node, if not visited calculate its distance and compare to min
                if(ptrV->visited == false){
                    ptrV->distance = ptrU->distance + ptrU->adj[j].weight;  //Calculate distance using u.distance and edge weight

                    if(minDistance > ptrV->distance){
                        minDistance = ptrV->distance;
                        minV = ptrV;                        //These temps are necessary because we don't want to change ptrU or ptrV while iterating
                        minU = ptrU;

                    }
                }
            }
        }
        //add vertex to solved
        solved.push_back(minV);
        //update minV's distance
        minV->distance = minDistance;
        //update minV's previous to be minU
        minV->previous = minU;
        //mark minV as visited
        minV->visited = true;
    }

    finalPath.push_back(minV);          //Add ending city, then all cities previous to it, to a vector for printing
    while(minV->previous != NULL){
        minV = minV->previous;
        finalPath.push_back(minV);
    }

    int charges = calculateCharge(minDistance);

    cout << "Also, the shortest path will take " <<minDistance<< " miles, " <<charges<<" charges, and pass through these cities: ";
    for(int i = finalPath.size()-1; i > 0; i--){
        cout<<finalPath.at(i)->name << ", ";
    }
    //cout<<"111"<<endl;
    cout<<finalPath.at(0)->name;
    cout << endl;
    //cout<<"222"<<endl;
    printChargingStations(finalPath,2);

    //return minDistance;
}

/*
Function Prototype:
void Graph::printChargingStations(vector<vertex*>,int)

Function Description:
This function first verifies that a given path, either shortest path or shortest distance, first has Superchargers
on it, then goes through the given path and prints out the cities that have charging stations.

Example:
Graph cg;
vector<vertex*> path;
cg.printChargingStations(path,1);

Pre-conditions: a vector of vertex pointers that is filled with cities, and 1 or 2,
    depending which path we are trying to print
Post-conditions: print cities in the given path that have charging stations
*/
void Graph::printChargingStations(vector<vertex*> v, int whichPath){
    bool hasSuperchargers = false;              //Checker for if print below is necessary
    if(whichPath == 1){
        for(int i = 0; i < v.size(); i++){      //Iterate through shortest path vector looking for a city with a Supercharger
            if(v[i]->chargeStation){
                hasSuperchargers = true;
                break;
            }
        }
    }
    else{
        for(int i = v.size()-1; i>=0; i--){     //Iterate through shortest distance vector looking for a city with a Supercharger
            if(v[i]->chargeStation){
                hasSuperchargers = true;
                break;
            }
        }
    }
    if(!hasSuperchargers){
        cout << "Unfortunately there are no Tesla Superchargers on this route." << endl;
        return;
    }

    cout<<"The cities on this route that have Tesla Superchargers are: ";
    bool found = false;
    if(whichPath == 1){
        for(int i=0;i<v.size();i++){        //Iterate through shortest path vector
            if(v[i]->chargeStation){
                if(!found){
                    found = true;
                    cout<<v[i]->name;
                }else{
                    cout<<", "<<v[i]->name;
                }
            }
        }
    }else{
        bool found1 = false;
        for(int i=v.size()-1;i>0;i--){      //Iterate through shortest distance vector
            if(v[i]->chargeStation){
                if(!found1)
                {
                    found1 = true;
                    cout << v[i]->name;
                }
                else
                {
                    cout << ", " << v[i]->name;
                }
            }
        }
        if(v[0]->chargeStation)
        {
            cout << ", " << v[0]->name;
        }
    }
    cout << endl << endl;
}


/*
Function Prototype:
void Graph::citiesWithinReach(string,int);

Function Description:
This function takes in the amount of time the user has to drive, then uses Djikstra's algorithm and the
returnShortestPath function to determine all cities that can be reached in that amount of time.

Example:
Graph cg;
vector<vertex> possibleCities;
cg.citiesWithinReach("Boulder", 10);

Pre-conditions: The starting city must be a valid node in an already built graph,
    and hours to travel must be an int >0
Post-conditions: Print cities that can be reached
*/
void Graph::citiesWithinReach(string startCity, int hoursToTravel)
{
    bool foundCity = false;
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i].name == startCity)
        {
            foundCity = true;
        }
    }
    if(foundCity)
    {
        vector <vertex> possibleCities;     //Will hold all cities that can be reached, to print later
        int time = hoursToTravel;
        int indexLocation;
        int distancePossible = time * 55;        //Average of 60MPH for the entire time, counting stops and >65MPH roads

        for(int i = 0; i < vertices.size(); i++)
        {
            int newDistance = returnShortestDistance(startCity, vertices[i].name);  //returnShortestDist is still Djikstra's algorithm, but returns rather than void
            if(newDistance <= distancePossible)
            {
                possibleCities.push_back(vertices[i]);      //This city can be reached in the amount of time available
            }
        }

        if(!possibleCities.empty())
        {
            cout << "The cities that you can reach in " << hoursToTravel << " hours are: ";
            for(int i = 0; i < possibleCities.size()-1; i++)
            {
                if(possibleCities[i].name == startCity)
                {
                }
                else
                {
                    cout << possibleCities[i].name << ", ";
                }
            }
            int lastPrint = possibleCities.size()-1;
            cout << possibleCities[lastPrint].name << endl << endl;
        }
        else
        {
            cout << "Unfortunately there are no cities that you can reach in the amount of time you have." << endl << endl;
        }
    }
    else
    {
        cout << "That city is not an option, please enter again." << endl;
    }
}


/*
Function Prototype:
void Graph::returnShortestDistance(string,string);

Function Description:
This function  uses Djikstra's algorithm to calculate the minimum distance between two nodes and
then returns that value, after verifying that both nodes exist in the graph.

Example:
Graph cg;
vector<vertex*> solved;
cg.returnShortestDistance("Boulder", "Seattle");

Pre-conditions: Both cities must exist in an already built graph
Post-conditions: The minimum distance between the nodes will be returned
*/
int Graph::returnShortestDistance(string v1, string v2){
    int i1 = -1;
    int i2 = -1;

    for(int i=0;i<vertices.size();i++){     //Find indexes of both cities in vector of cities
        if(vertices[i].name == v1){
            i1 = i;
        }
        if(vertices[i].name == v2){
            i2 = i;
        }
    }

    if(i1 == -1 || i2 == -1){
        cout<<"One or more cities doesn't exist"<<endl;
        return -1;
    }

    vector<vertex*> solved;
    vector<vertex*> finalPath;
    vertex* destPtr;
    int minDistance = INT_MAX;

    for(int i = 0; i < vertices.size(); i++){       //Setting all cities as not visited ensures they won't be missed during algorithm execution
        vertices[i].visited = false;
        vertices[i].previous = NULL;                //Previous should be NULL until start moving through graph and solving nodes
        vertices[i].distance = INT_MAX;             //Guaranteed to be larger than whatever valid distance is calculated during algorithm

        if(vertices[i].name == v1){
            vertices[i].visited = true;
            vertices[i].distance = 0;
            solved.push_back(&vertices[i]);     //Find starting city, push it into vector containing "solved" nodes
        }                                           //where solved means distance to it has been found

        if(vertices[i].name == v2){
            destPtr = &vertices[i];
        }
    }
    vertex* minV;
    vertex* minU;
    while(destPtr->visited == false){
        minDistance = INT_MAX;
        for(int i = 0; i < solved.size(); i++){     //Loop through nodes already solved and take each one, then look at its adjacencies
            vertex* ptrU = solved[i];
            for(int j = 0; j < ptrU->adj.size(); j++){
                vertex* ptrV = ptrU->adj[j].v;              //Take each adjacent node, if not visited calculate its distance and compare to min
                if(ptrV->visited == false){
                    ptrV->distance = ptrU->distance + ptrU->adj[j].weight;  //Calculate distance using u.distance and edge weight

                    if(minDistance > ptrV->distance){
                        minDistance = ptrV->distance;
                        minV = ptrV;                        //These temps are necessary because we don't want to change ptrU or ptrV while iterating
                        minU = ptrU;

                    }
                }
            }
        }
        //add vertex to solved
        solved.push_back(minV);
        //update minV's distance
        minV->distance = minDistance;
        //update minV's previous to be minU
        minV->previous = minU;
        //mark minV as visited
        minV->visited = true;
    }

    finalPath.push_back(minV);          //Add ending city, then all cities previous to it, to a vector for printing
    while(minV->previous != NULL){
        minV = minV->previous;
        finalPath.push_back(minV);
    }
    return minDistance;
}
