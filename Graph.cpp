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

Graph::Graph()
{

}

Graph::~Graph()
{
    //dtor
}
void Graph::addEdge(string v1, string v2, int weight){

    for(int i = 0; i < vertices.size(); i++){ //loop through all vertices
        if(vertices[i].name == v1){
            for(int j = 0; j < vertices.size(); j++){ //loop through and try to find the ending point
                if(vertices[j].name == v2 && i != j){
                    adjVertex av;
                    av.v = &vertices[j]; //v is going to store the address, it is just a pointer
                    av.weight = weight;
                    vertices[i].adj.push_back(av);

                    /*another vertex for edge in other direction
                    adjVertex av2;
                    av2.v = &vertices[i];
                    av2.weight = weight;
                    vertices[j].adj.push_back(av2);*/
                }
            }
        }
    }
}

void Graph::addVertex(string n){
    bool found = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == n){
            found = true;
            cout<<vertices[i].name<<" found."<<endl;
        }
    }
    if(found == false){
        vertex v;
        v.name = n;
        vertices.push_back(v);

    }
}

void Graph::displayEdges(){
    //loop through all vertices and adjacent vertices
    for(int i = 0; i < vertices.size(); i++){
        cout<<vertices[i].distID<<":"<<vertices[i].name<<"-->";
        for(int j = 0; j < vertices[i].adj.size(); j++){
            cout<<vertices[i].adj[j].v->name;
            if(j != vertices[i].adj.size()-1){
                cout<<"***";
            }
        }
        cout<<endl;
    }
}

void Graph::findDistricts(){
    int district = 1;
    int dist;
    for(int i=0;i<vertices.size();i++){
        if(vertices[i].distID == -1){
            bool found = false;
            for(int k=0;k<vertices[i].adj.size();k++){
                if(vertices[i].adj[k].v->distID != -1){
                    dist = vertices[i].adj[k].v->distID;
                    found = true;
                    break;
                }
            }
            if(found){
                vertices[i].distID = dist;
                for(int j=0;j<vertices[i].adj.size();j++){
                    vertices[i].adj[j].v->distID = dist;
                }
            }else{
                vertices[i].distID = district;
                for(int j=0;j<vertices[i].adj.size();j++){
                    vertices[i].adj[j].v->distID = district;
                }
                district++;
            }
        }else{
            for(int j=0;j<vertices[i].adj.size();j++){
                vertices[i].adj[j].v->distID = vertices[i].distID;
            }
        }
    }
}

void Graph::findShortestPath(string v1, string v2){
    int i1 = -1;
    int i2 = -1;

    queue<queueVertex> vQueue;
    vector<vertex*> path;
    queueVertex temp;
    int distance;
    queueVertex qv;
    qv.distance = 0;

    for(int i=0;i<vertices.size();i++){
        if(vertices[i].name == v1){
            i1 = i;
        }
        if(vertices[i].name == v2){
            i2 = i;
        }
    }
    if(vertices[0].distID == -1){
        cout<<"Please identify the districts before checking distances"<<endl;
        return;
    }
    if(i1 == -1 || i2 == -1){
        cout<<"One or more cities doesn't exist"<<endl;
        return;
    }
    if(vertices[i1].distID != vertices[i2].distID){
        cout<<"No safe path between cities"<<endl;
        return;
    }

    //setting all the visited to false
    for(int i=0;i<vertices.size();i++){
        vertices[i].visited = false;
    }

    //find starting city in vertices
    for(int i=0;i<vertices.size();i++){
        if(vertices[i].name == v1){
            vertices[i].visited = true;
            qv.path.push_back(&vertices[i]);
            vQueue.push(qv);
            break;
        }
    }

    while(!vQueue.empty()){
        qv = vQueue.front();
        vQueue.pop();
        for(int i=0;i<qv.path.back()->adj.size();i++){
            if(qv.path.back()->adj[i].v->visited == false){
                    path = qv.path;
                    qv.path.back()->adj[i].v->visited = true;
                    distance = qv.distance + 1;
                    path.push_back(qv.path.back()->adj[i].v);
                    temp.path = path;
                    temp.distance = distance;
                    if(temp.path.back()->name == v2){
                        //print everything
                        cout<<distance;
                        for(int j = 0;j<temp.path.size();j++){
                            cout<<","<<temp.path[j]->name;
                        }
                        cout<<endl;
                        return;
                    }
                    else{
                        vQueue.push(temp);
                    }
            }
        }
    }
}

int Graph::findShortestDistance(string v1, string v2){
    int i1 = -1;
    int i2 = -1;

    //finding the indexes of the two cities
    for(int i=0;i<vertices.size();i++){
        if(vertices[i].name == v1){
            i1 = i;
        }
        if(vertices[i].name == v2){
            i2 = i;
        }
    }
    //checking all of the cases
    if(vertices[0].distID == -1){
        cout<<"Please identify the districts before checking distances"<<endl;
        return;
    }
    if(i1 == -1 || i2 == -1){
        cout<<"One or more cities doesn't exist"<<endl;
        return;
    }
    if(vertices[i1].distID != vertices[i2].distID){
        cout<<"No safe path between cities"<<endl;
        return;
    }

    vector<vertex*> solved;
    vector<vertex*> finalPath;
    vertex* destPtr;
    int minDistance = INT_MAX;

    for(int i = 0; i < vertices.size(); i++)
    {
        vertices[i].visited = false;
        vertices[i].previous = NULL;
        vertices[i].distance = INT_MAX;

        if(vertices[i].name == v1)
        {
            vertices[i].visited = true;
            vertices[i].distance = 0;
            solved.push_back(&vertices[i]);
        }

        if(vertices[i].name == v2)
        {
            destPtr = &vertices[i];
        }
    }
    vertex* minV;
    vertex* holdU;
    while(destPtr->visited == false)
    {
        minDistance = INT_MAX;
        for(int i = 0; i < solved.size(); i++)
        {
            vertex* ptrU = solved[i];
            for(int j = 0; j < ptrU->adj.size(); j++)
            {
                vertex* ptrV = ptrU->adj[j].v;
                if(ptrV->visited == false)
                {
                    //Calculate distance using u.distance and edge weight
                    ptrV->distance = ptrU->distance + ptrU->adj[j].weight;

                    //Find min dist and store vertex information
                    if(minDistance > ptrV->distance)
                    {
                        minDistance = ptrV->distance;
                        minV = ptrV;
                        holdU = ptrU;

                    }
                }
            }
        }
        //add vertex to solved
        solved.push_back(minV);
        //update minV's distance
        minV->distance = minDistance;
        //update minV's previous to be holdU
        minV->previous = holdU;
        //mark minV as visited
        minV->visited = true;
    }

    finalPath.push_back(minV);
    while(minV->previous != NULL)
    {
        minV = minV->previous;
        finalPath.push_back(minV);
    }

    cout<<minDistance;
    for(int i = finalPath.size()-1; i > 0; i--)
    {
        cout<<","<<finalPath.at(i)->name;
    }
    cout<<","<<finalPath.at(0)->name;
    cout << endl;

    return minDistance;
}
