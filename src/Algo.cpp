#include"keyValueStore.h"
#include"Graph.h"
#include"Algo.h"
#include"debug.h"
#include<ctime>
#include<cstdlib>
#include<iostream>
#include<thread>

#define THD 8
using namespace std;


mutex Ant_dist_lock;

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
//        cout<<" neighbour size : "<<confSet.size()<<endl;
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


set<CONF> Ant::filterCONF(Graph* g,set<CONF> in) {
    set<CONF> out;
    for( auto it = in.begin() ; it!=in.end() ; it++ )
        if( !g->isVisit(*it) )
            out.insert(*it);
    return out;
}

/*
    This is to be invoked by a thread in ANT
*/
void Ant::antThread(Graph* g,CONF initConf,Ant* antobj, map<int,int>* globDist) {

    set<CONF> confSet;    // the set of configuration nodes
    CONF curr;      // the current configuration
    int tmp1,tmp2;
    int n = g->getNodeCnt(); 
    
    map<int,int> dist;
    // initialize the dist structure in the graph
    for( int i=1 ; i<=n ; i++ )
       dist[i]=1000000000;      // set it to a high number
    dist[ initConf[0] ] = 0;

    confSet =  g->getNeighbour(initConf) ; 
    g->markVisit( initConf );
    curr = initConf;


    int loopCount=0;
    while( 1 ) {
        loopCount++;
        if( confSet.size() == 0 ) 
            break;
 //       cout<<" neighbour size : "<<confSet.size()<<endl;
        tmp1 = rand() % confSet.size() ;  // decide the next node to visit
        auto it = confSet.begin();
        for( ; it!=confSet.end() && tmp1>0 ; it++ ) 
            tmp1--;

        curr = *it;  // set the current value of configuration
        dist[ curr[0] ] = min( dist[curr[0]], g->visitCnt() );
        g->markVisit( curr );        // mark the configuration visited
        confSet = filterCONF( g, g->getNeighbour( curr ) );  
    }
    // update the global distance matrix in this block
    {
        lock_guard<mutex> lck( Ant_dist_lock );
        for( int i=1 ; i<=n ; i++ )
            (*globDist)[i] = min( dist[i], (*globDist)[i] );
    }

    cout<<"Curr thread iteration count : "<<loopCount<<endl;
}


void Ant::iterate() {
    srand(time(NULL));

    g = new Graph;
    g->readFromFile(datasetName);   // read data from file
    int n = g->getNodeCnt(); 
    
    // initialize the dist structure in the graph
    for( int i=1 ; i<=n ; i++ )
       dist[i]=1000000000;      // set it to a high number
    dist[ initConf[0] ] = 0;

    cout<<"Number of nodes in graph : "<<n<<endl;


    // Spawn other threads from here.
    vector<thread> vthread;    // vector of threads in ACO
    for( int i=0 ; i<THD ; i++ )
        vthread.push_back( (thread(antThread,g,initConf,this,&dist)) );

    // WAIT FOR THREADS TO COMPLETE THEIR WORK

    for( int i=0 ; i<THD ; i++ )
        vthread[i].join();
    vthread.clear();


    int totVisit = 0 ;
    for( int i=1 ; i<=n ; i++ ) 
        if( g->isnVisit(i) )
            totVisit++;

    cout<<" Total visited nodes by robot : "<<totVisit<<endl;
    cout<<" Visit count : "<<g->visitCnt()<<endl; 
    for( auto it = dist.begin() ; it!= dist.end() ; it++ )
        cout<<it->first<<" : "<<it->second<<endl;
    cout<<" Exiting the loop "<<endl;
}


