#include"keyValueStore.h"
#include"Graph.h"
#include"Algo.h"
#include"debug.h"
#include<ctime>
#include<cstdlib>
#include<iostream>
using namespace std;


/*
    The random ANT algo below this line
*/

void RandomAnt::setInit(CONF conf) {
    initConf = conf; 
}


void RandomAnt::setDataset(string filename) {
    datasetName = filename;
}


set<CONF> RandomAnt::filterCONF(set<CONF> in) {
    
    set<CONF> out;
    for(auto it = in.begin() ; it!=in.end() ; it++ )
        if( tabu_list.find(*it) == tabu_list.end() )
            out.insert(*it);
    return out;
}


/*
    For the iteration of the current Ant thread
*/
void RandomAnt::iterate() {
    srand(time(NULL));
    tabu_list.clear();

    g = new Graph;
    g->readFromFile(datasetName);   // read data from file
    int n = g->getNodeCnt(); 
    cout<<"Number of nodes in graph : "<<n<<endl;
    set<CONF> confSet;    // the set of configuration nodes
    CONF curr;      // the current configuration
    int tmp1,tmp2;

    confSet =  g->getNeighbour(initConf) ; 
    tabu_list.insert( initConf );
    g->markVisit( initConf );
    curr = initConf;

    // print all the configuration in confSet
    cout<<" printing confSet of size : "<<confSet.size()<<endl;
    printCONF(g,initConf);
    for( auto it : confSet )
        printCONF(g, it);
    
    cout<<"--------------------------------------------------"<<endl;
    while( 1 ) {
        if( confSet.size() == 0 ) 
            break;
        cout<<" neighbour size : "<<confSet.size()<<endl;
        tmp1 = rand() % confSet.size() ;  // decide the next node to visit
        auto it = confSet.begin();
        for( ; it!=confSet.end() && tmp1>0 ; it++ ) 
            tmp1--;

        curr = *it;  // set the current value of configuration
        tabu_list.insert( curr );    // insert this in the tabu_list
        g->markVisit( curr );        // mark the configuration visited
        confSet = filterCONF( g->getNeighbour( curr ) );  
    }
    int totVisit = 0 ;
    for( int i=1 ; i<=n ; i++ ) 
        if( g->isnVisit(i) )
            totVisit++;

    cout<<" Total visited nodes by robot : "<<totVisit<<endl;
    cout<<" Visit count : "<<g->visitCnt()<<endl; 
    cout<<" Exiting the loop "<<endl;
}

//--------------------------------------------------------------

/*
    This will be a standard ACO implementation with multiple ants but without pheromone
*/

void Ant::setInit(CONF conf) {
    initConf = conf;
}


void Ant::setDataset(string filename) {
    datasetName = filename;
}


set<CONF> Ant::filterCONF(set<CONF> in) {
    set<CONF> out;
    for( auto it = in.begin() ; it!=in.end() ; it++ )
        if( !g->isVisit(*it) )
            out.insert(*it);
    return out;
}


void Ant::iterate() {
    srand(time(NULL));

    g = new Graph;
    g->readFromFile(datasetName);   // read data from file
    int n = g->getNodeCnt(); 
    cout<<"Number of nodes in graph : "<<n<<endl;
    set<CONF> confSet;    // the set of configuration nodes
    CONF curr;      // the current configuration
    int tmp1,tmp2;

    confSet =  g->getNeighbour(initConf) ; 
    g->markVisit( initConf );
    curr = initConf;

    // print all the configuration in confSet
    cout<<" printing confSet of size : "<<confSet.size()<<endl;
    printCONF(g,initConf);
    for( auto it : confSet )
        printCONF(g, it);
    
    cout<<"--------------------------------------------------"<<endl;
    while( 1 ) {
        if( confSet.size() == 0 ) 
            break;
        cout<<" neighbour size : "<<confSet.size()<<endl;
        tmp1 = rand() % confSet.size() ;  // decide the next node to visit
        auto it = confSet.begin();
        for( ; it!=confSet.end() && tmp1>0 ; it++ ) 
            tmp1--;

        curr = *it;  // set the current value of configuration
        g->markVisit( curr );        // mark the configuration visited
        confSet = filterCONF( g->getNeighbour( curr ) );  
    }
    int totVisit = 0 ;
    for( int i=1 ; i<=n ; i++ ) 
        if( g->isnVisit(i) )
            totVisit++;

    cout<<" Total visited nodes by robot : "<<totVisit<<endl;
    cout<<" Visit count : "<<g->visitCnt()<<endl; 
    cout<<" Exiting the loop "<<endl;
}


