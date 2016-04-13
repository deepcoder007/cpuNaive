#ifndef GRAPH
#define GRAPH

#include<string>
#include<vector>
#include<cstring>
#include<set>
#include<mutex>
#include<shared_mutex>
#include"keyValueStore.h"

// cost of moving a robot
#define ROBOT_COST 1

// cost of moving an obstacle
#define OBS_COST 1

/*
    NOTE : Graph will have nodes starting from 1, in bitset this factor 
    should be considered to avoid wastage of space.
    NOTE 2 : The position of robot is not marked vacant, this was a potential source of bug earlier
*/

class Graph
{
private:
    int n;          // Number of nodes in graph
    //int grid[100][100];    // to store the adjacency matrix of underlying graph
    map<int,set<int> > mgrid;  // an adjacency list for grid
    map<pair<int,int>, float> gweight;   // weight of edges in underlying g
    
    keyValueStore storage;   // to store the pheromone content
    set<CONF> visited[N_VAL+1];       // to store the visited configuration nodes
    set<int> nvisited;       // to store the visited robot pos

    shared_timed_mutex phero_mutex[N_VAL+1];       // mutex while accessing the storage structure
    shared_timed_mutex tag_mutex[N_VAL+1];         // mutex for tagging the visited nodes
    shared_timed_mutex univ_tag_mutex;

    // private functions for manipulation of underlying graph
    bool gAdjacent(int x,int y);
    vector<int> gNeighbors(int x);
public:
    void readFromFile(string name); // read from file in `data` directory
    set<pair<CONF,int> > getNeighbour(CONF conf); // neighbours of this configuration , along with the cost of each configuration
    bool isNeighbour(CONF conf1,CONF conf2); // are they neighbouring

    float getPhero(CONF conf);  // pheromone content  
    bool setPhero(CONF conf, float value);
    int getNodeCnt();       // returns the number of nodes in the graph

    void markVisit(CONF conf);
    bool isVisit(CONF conf);   // checks if the node is visited
    bool isnVisit(int k);
    void clearVisit(CONF conf);   // clear the visited nodes 
    int visitCnt();            // count the number of visited nodes

    bool isVacant(CONF key,int pos);   // is the position empty
    CONF setVac(CONF key,int pos);     // set the position vacant
    CONF unsVac(CONF key,int pos);     // unset the position
    bool isValid(CONF key);     // is it a valid configuration 
    int cntVac(CONF key);       // count vacant nodes in configuration
    int containerSize();
};

#endif
