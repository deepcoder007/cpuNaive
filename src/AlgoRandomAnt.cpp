//#include"keyValueStore.h"
//#include"Graph.h"
#include"Algo.h"
#include"debug.h"
#include<ctime>
#include<cstdlib>
#include<iostream>
#include<thread>
#include<utility>
#include<random>

using namespace std;


//--------------------------------------------------------------
//      The Random ANT implementation
//--------------------------------------------------------------


void RandomAnt::setInit(CONF conf) {
    initConf = conf; 
}


void RandomAnt::setDataset(string filename) {
    datasetName = filename;
}


set<pair<CONF,int> > RandomAnt::filterCONF(set<pair<CONF,int> > in) {
    
    set<pair<CONF,int> > out;
    for(auto it = in.begin() ; it!=in.end() ; it++ )
        if( tabu_list.find( it->first ) == tabu_list.end() )
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
    set<pair<CONF,int> > confSet;    // the set of configuration nodes
    pair<CONF,int> curr;      // the current configuration
    int tmp1,tmp2;

    confSet =  g->getNeighbour( initConf ) ; 
    tabu_list.insert( initConf );
    g->markVisit( initConf );
    curr = make_pair(initConf, 0);

    // print all the configuration in confSet
//    cout<<" printing confSet of size : "<<confSet.size()<<endl;
//    printCONF(g,initConf);
//   for( auto it : confSet )
//      printCONF(g, it.first );
    
    cout<<"--------------------------------------------------"<<endl;
    for( int zz = 0 ; zz < 1000 ; zz++ ) {
        cout<<zz<<endl;
        if( confSet.size() == 0 ) 
            break;
//        cout<<" neighbour size : "<<confSet.size()<<endl;
        tmp1 = rand() % confSet.size() ;  // decide the next node to visit
        auto it = confSet.begin();
        for( ; it!=confSet.end() && tmp1>0 ; it++ ) 
            tmp1--;

        curr = *it;  // set the current value of configuration
        tabu_list.insert( curr.first );    // insert this in the tabu_list
        g->markVisit( curr.first );        // mark the configuration visited
        confSet = filterCONF( g->getNeighbour( curr.first ) );  
    }
    int totVisit = 0 ;
    for( int i=1 ; i<=n ; i++ ) 
        if( g->isnVisit(i) )
            totVisit++;

    cout<<" Total visited nodes by robot : "<<totVisit<<endl;
    cout<<" Visit count : "<<g->visitCnt()<<endl; 
    cout<<" Exiting the loop "<<endl;
}

