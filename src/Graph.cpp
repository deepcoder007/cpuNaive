#include"Graph.h"
#include<string>
#include<fstream>
#include<vector>
#include<set>
#include<sstream>
#include<cassert>
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<unistd.h>
using namespace std;


#if defined UNORDERED

unsigned long hashPAIRI2( pair<int,int> key ) {
    return (key.first*key.second)%INT_MAX; 
}

bool equalPAIRI2( pair<int,int> key1, pair<int,int> key2 ) {
    return ( key1.first == key2.first && key1.second == key2.second );
}

#endif



// Function to split the string by the given delimiter
// NOTE:  THREAD_SAFE
vector<string> split(string str, char delimiter=' ') {
    vector<string> interval;
    stringstream ss(str);
    string tok;
    while( getline(ss, tok, delimiter) ) {
        interval.push_back(tok);
    }
    return interval;
}


/*
    Checks if x and y are adjacent nodes in the underlying graph
*/
bool Graph::gAdjacent(int x,int y) {
    if( mgrid[x].find(y) != mgrid[x].end() )
        return true;
    else
        return false;
}

/*
    Returns a vector of neighbours of node x in the underlying graph
    NOTE: THREAD_SAFE
    TODO : check if we can do without unique_lock and use shared_lock for better performance
*/
vector<int> Graph::gNeighbors(int x) {
    vector<int> out;
    // first lock the mgrid structure 
    unique_lock<shared_timed_mutex> lck(mgrid_mutex[x]);
    for( int  i=1; i<=n ; i++ )
        if( mgrid[x].find(i) != mgrid[x].end() )
            out.push_back(i);
    return out;
}

/*
    Is position pos is vacant in key
    NOTE: THREAD_SAFE 
*/
inline bool Graph::isVacant(CONF key, int pos) {
    if( pos == key[0] )   // if the position has the robot
        return false;
    int i,j;
    i=pos/INT_SZ; i++;   // the array index
    j=pos%INT_SZ;        // the bitindex
    if( (key[i] & (1<<j)) == 0 )  // if not vacant 
        return false;
    else
        return true;
}

/*
    Set the position vacant in the key and return it
    NOTE: THREAD_SAFE
*/
inline CONF Graph::setVac(CONF key,int pos) {
    if( pos == key[0] )    // i.e. an error condition
    {
        CONF key2 ;
        key2[0]=-1;
        return key2;
    }
    int i,j;
    i = pos/INT_SZ ; i++;
    j = pos%INT_SZ;
    key[i] |= (1<<j);
    return key;
}

/*
    Mark the position as filled with obstacle in the node
    NOTE: THREAD_SAFE
*/
inline CONF Graph::unsVac(CONF key,int pos) {
    if( pos == key[0] )  // if that position has robot, no change
        return key;
    int i,j;
    i = pos/INT_SZ ; i++;
    j = pos%INT_SZ;
    key[i] &= ~(1<<j);
    return key;
}

/*
    Returns the number of vacant nodes in the configuration 
    NOTE: THREAD_SAFE
*/
inline int Graph::cntVac(CONF key) {
#ifdef DEBUG
    assert( isValid(key) );  // checks if this is a valid node
#endif
    int i;
    int out=0;
    for( i=1 ; i<n ; i++ ) 
        if( isVacant(key, i) )
            out++;
    return (out);   // account for the robot also
}

/*
    Check if this is a valid configuration
    NOTE: THREAD_SAFE
*/
inline bool Graph::isValid(CONF key) {
    if( isVacant(key, key[0]) )
        return true;
    else 
        return false;
}

/*
    Read the underlying graph from the text file
    NOTE: Called only once in program
*/
void Graph::readFromFile(string name) {
   string line;
   int a,b;
   int w;   // weight of graph
   cout<<"file : "<<"data/"+name<<endl;
   ifstream infile("data/"+name);
   while( getline(infile, line) ) {
       vector<string> data = split(line,','); 
       a = atoi(data[0].c_str());
       b = atoi(data[1].c_str());
       w = 1;
       if( data.size() > 2 ) // i.e. it has weight values also
           w = atoi(data[2].c_str());
       if( a==b ) 
           continue;
       a++ ; b++ ;
       n = max( n, max(a,b) );
       // for unweighted directed graph;
       mgrid[a].insert(b);     // insert a directed edge
       // for weights 
       gweight[ make_pair(a,b) ] = w;
   }
   cout<<"No. of weights : "<<gweight.size()<<endl;

}


/*
    Returns the set of neighbours of the current configuration
    conf -> the configuration for which the neighbors are to be found
    TODO : optimization possible, currently it is brute force approach
*/
set<pair<CONF,int> > Graph::getNeighbour(CONF conf) {

    set<pair<CONF,int> > out;   // to be returned 

    int rPos = conf[0];
    int i,j;
    CONF tmpConf;      // temp conf
    vector<int> nVector;     // vector to hold neighbors


    // first move the robot 
    nVector = gNeighbors(rPos);
    for( i=0 ; i<nVector.size() ; i++ )  {
        if( isVacant(conf, nVector[i]) ) {
            tmpConf = conf;
            tmpConf[0] = nVector[i];
            out.insert(make_pair( tmpConf, ROBOT_COST*gweight[ make_pair(rPos,tmpConf[0]) ]));
        }
    }

    // move the obstacles
    for( i=1 ; i<=n ; i++ ) {
        if( i == conf[0] )  // skip this iteration is current node has robot
            continue;

        if( !isVacant(conf,i) ) {  
            nVector.clear();
            nVector = gNeighbors(i); 
            for( j=0 ; j<nVector.size() ; j++ ) {
                if( isVacant(conf, nVector[j] )) {
                    out.insert( make_pair( setVac( unsVac(conf, nVector[j] ), i), OBS_COST*gweight[ make_pair(i, nVector[j] ) ]));
                }
            }
        }
    }
    return out;
}

/*
    is conf2 a neighbour of conf1
    NOTE: THREAD_SAFE
*/
bool Graph::isNeighbour(CONF conf1,CONF conf2) {

    int vac1 = cntVac(conf1);
    int vac2 = cntVac(conf2);

    if( vac1 != vac2 )
        return false;
    if( conf1[0] != conf2[0] )  // change in position of robot
    {
       // check if rest of the position are same and output accordingly
       bool flag = true;
       for(int i=1; i<KEY_SZ ;i++ ) 
           if( conf1[i]!=conf2[i] )
               flag = false;

       return flag;
    }
    
    // change due to obstacles
    int diff = 0 ;    //count the number of diff. positions
    int p1= -1 , p2=-1 ;  // p1=(source) , p2=(dest)
    bool v1 , v2;
    // check at all the positions
    for( int i=1 ; i<=n ; i++ ) {
       v1 = isVacant(conf1,i);
       v2 = isVacant(conf2,i);
       if( v1 != v2 ) {
           diff++;    // a difference found
           if( v2 ) p1 = i;
           else     p2 = i;
       }
    }

    if( diff!=2 || p1 == -1 || p2 == -1 )
        return false;
    else
        return true;
}

/*
    Returns the pheromone content of the graph
    NOTE: THREAD_SAFE
*/
float Graph::getPhero(CONF conf) {
    // lock before doing it
    shared_lock<shared_timed_mutex> lck(phero_mutex[conf[0]]);
    return storage.getValue(conf);
}

/*
    Sets the value of pheromone in the graph
    NOTE: THREAD_SAFE
*/
bool Graph::setPhero(CONF conf, float value) {

    // lock before doing this
    if( value < PHERO_MIN )
        value = PHERO_MIN;
    else if( value > PHERO_MAX )
        value = PHERO_MAX;

    unique_lock<shared_timed_mutex> lck(phero_mutex[conf[0]]);
    storage.setValue(conf, value);
    return true;
}

/*
    Adds to the value of pheromone in the graph
    NOTE: THREAD_SAFE
*/
bool Graph::addPhero(CONF conf, float value) {

    // lock before doing this
    // retrieve the old value of phero first
    unique_lock<shared_timed_mutex> lck(phero_mutex[conf[0]]);
    float curr_tmp = storage.getValue(conf);
    if( curr_tmp == -1 ) {
        if( value < PHERO_MIN )
            value = PHERO_MIN;
        else if( value > PHERO_MAX )
            value = PHERO_MAX;
        storage.setValue(conf, value);
    } else {
        value = value + curr_tmp;
        if( value < PHERO_MIN )
            value = PHERO_MIN;
        else if( value > PHERO_MAX )
            value = PHERO_MAX;
        storage.setValue(conf, value);
    }
    return true;
}

/*
    Checks if pheromone exist for the given configuration
*/
bool Graph::existPhero(CONF conf) {
    // lock before doing this
    unique_lock<shared_timed_mutex> lck(phero_mutex[conf[0]]);
    return storage.keyExist(conf);
}


/*
    Returns the number of nodes in the graph
    NOTE: THREAD_SAFE
*/
int Graph::getNodeCnt() {
    return n;
}

/*
    Mark the node visited
    NOTE: THREAD_SAFE
*/
void Graph::markVisit(CONF conf) {
    unique_lock<shared_timed_mutex> lck(tag_mutex[conf[0]]);
    visited[conf[0]].insert(conf);
    nvisited.insert(conf[0]);
}

/*
    Checks if the node is visited
    NOTE: THREAD_SAFE
*/
bool Graph::isVisit(CONF conf) {
    shared_lock<shared_timed_mutex> lck(tag_mutex[conf[0]]);
    if( visited[conf[0]].find(conf) == visited[conf[0]].end() )
        return false;
    else
        return true;
}

/*
    Checks if node k is visited by this key
    NOTE: THREAD_SAFE
*/
bool Graph::isnVisit(int k) {
    shared_lock<shared_timed_mutex> lck(univ_tag_mutex);
    if( nvisited.find(k) == nvisited.end() ) 
        return false;
    else 
        return true;
}

/*
    Clear the list of visited nodes before start of next ACO iteration
*/
void Graph::clearVisit(CONF conf) {
    for( int i=1 ; i<= N_VAL ; i++ )
        visited[i].clear();
    nvisited.clear();
}

/*
    Returns the number of visited nodes
*/
int Graph::visitCnt() {
    int res = 0;
    for( int i=1 ; i<= N_VAL ; i++ )
        res += visited[i].size();
    return res;
}


/*
    returns the size of the underlying key-value store
*/
int Graph::containerSize() {
    return storage.getSize();
}

