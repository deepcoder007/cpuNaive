//#include"keyValueStore.h"
//#include"Graph.h"
#include"Algo.h"
//#include"debug.h"
#include<ctime>
#include<cstdlib>
#include<iostream>
#include<thread>
#include<utility>
#include<random>

using namespace std;

mutex Ant_dist_lock_1;

//--------------------------------------------------------------
//      The ANT implementation
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


set<pair<CONF,int> > Ant::filterCONF(Graph* g,set<pair<CONF,int> > in) {
    set<pair<CONF,int> > out;
    for( auto it = in.begin() ; it!=in.end() ; it++ )
        if( !g->isVisit(it->first) )
            out.insert(*it);
    return out;
}


/*
    This is to be invoked by a thread in ANT
*/
void Ant::antThread(Graph* g,CONF initConf,Ant* antobj, map<int,int>* globDist) {

    set<pair<CONF,int> > confSet;    // the set of configuration nodes
    pair<CONF,int> curr;      // the current configuration
    int tmp1,tmp2;
    int n = g->getNodeCnt(); 
    int curr_cost = 0 ;         // records the cost of the current path
    
    map<int,int> dist;
    // initialize the dist structure in the graph
    for( int i=1 ; i<=n ; i++ )
       dist[i]=1000000000;      // set it to a high number
    dist[ initConf[0] ] = 0;

    confSet =  g->getNeighbour(initConf) ; 
    g->markVisit( initConf );
    curr = make_pair( initConf, 0 );

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
        g->setPhero( curr.first , 1.0 );

        curr_cost += curr.second;   // add the cost of this node
        dist[ curr.first[0] ] = min( dist[curr.first[0]], curr_cost );
        g->markVisit( curr.first );        // mark the configuration visited
        confSet = filterCONF( g, g->getNeighbour( curr.first ) );  

    }
    // update the global distance matrix in this block
    {
        lock_guard<mutex> lck( Ant_dist_lock_1 );
        for( int i=1 ; i<=n ; i++ )
            (*globDist)[i] = min( dist[i], (*globDist)[i] );

    }

    cout<<"Total cost of the current path : "<<curr_cost<<endl;
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
        vthread.push_back( (thread(antThread, g, initConf, this, &dist)) );

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

