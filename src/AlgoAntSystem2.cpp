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

mutex Ant_dist_lock_4;

//--------------------------------------------------------------
//      The "ANT SYSTEM 2"  implementation
//      Int this version we have weight reduction after each 
//      iteration to allow for exploring newer paths
//--------------------------------------------------------------

/*
    This will be a standard ACO implementation with multiple ants but without pheromone
*/

void AntSystem2::setInit(CONF conf) {
    initConf = conf;
}


void AntSystem2::setDataset(string filename) {
    datasetName = filename;
}


/*
    Removes the configurations which are already visited
*/
set<pair<CONF,int> > AntSystem2::filterCONF(Graph* g,set<pair<CONF,int> > in) {
    set<pair<CONF,int> > out;
    for( auto it = in.begin() ; it!=in.end() ; it++ )
        if( !g->isVisit(it->first) )
            out.insert(*it);
    return out;
}


/*
    Returns the next configuration from the set
    curr    : The position of current configuration of ANT
    confSet : configuraiton set of neighbours of atn
*/
pair<CONF,int> AntSystem2::getNextConf( CONF curr, set<pair<CONF,int> >& confSet, Graph* g ) {

    vector<pair<CONF,int> > vConf;  // stores the list of configuration
    vector<int>  vProb;     // stores the probabilities
    CONF itConf;    // stores the CONF of current it
    float currPhero;        // the pheromone content of current graph

    // loop over the confSet
    for( auto it = confSet.begin() ; it != confSet.end() ; it++ ) {
        vConf.push_back(*it);  // push the [pair<CONF,int>] pair as it is

        itConf = it->first;

        // if pheromone value does not exist as of now
        currPhero = PHERO_MAX;
        if( g->existPhero(itConf) )
            currPhero = g->getPhero(itConf);

        if( itConf[0] == curr[0] ) {
            // CASE : robot position does not change
            vProb.push_back( currPhero );
        } else if( g->isnVisit(itConf[0]) ) {
            // CASE : the position was earlier visited by robot
            //        higher premium for accessing it
            vProb.push_back( currPhero*EXPLORE_DIFF );
        } else {
            // CASE : the position was never visited by robot
            //        highest premium for accessing it
            vProb.push_back( currPhero*EXPLORE_DIFF*EXPLORE_MULTI );
        }
    }
    random_device rd;
    discrete_distribution<int> dist(vProb.begin(), vProb.end());
    return vConf[ dist(rd) ];
}


/*
    This is to be invoked by a thread in ANT
*/
void AntSystem2::antThread(Graph* g,
                CONF initConf, AntSystem2* antobj, 
                map<int,int>* globDist,int maxloopCount) {

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
    for( loopCount=0 ; loopCount < maxloopCount ; loopCount ++ )
    {
 //       cout<<" Loop Number : "<<loopCount<<endl;
        if( confSet.size() == 0 ) 
            break;

        // cout<<" neighbour size : "<<confSet.size()<<endl;

        // Generate numbers according to a distribution 

        //tmp1 = rand() % confSet.size() ;  // decide the next node to visit

        //auto it = confSet.begin();
        //for( ; it!=confSet.end() && tmp1>0 ; it++ ) 
        //    tmp1--;
        //curr = *it;  // set the current value of configuration

        curr = getNextConf( curr.first, confSet, g );

        // call this if 'curr' is already not in the list
        // IMP: This small bug gave me a lot of pain and inaccurate results
        if( !g->existPhero( curr.first ) )
            g->setPhero( curr.first , PHERO_MAX );

        curr_cost += curr.second;   // add the cost of this node
        dist[ curr.first[0] ] = min( dist[curr.first[0]], curr_cost );
        g->markVisit( curr.first );        // mark the configuration visited
        confSet = filterCONF( g, g->getNeighbour( curr.first ) );  

    }
    // update the global distance matrix in this block
    {
        lock_guard<mutex> lck( Ant_dist_lock_4 );
        for( int i=1 ; i<=n ; i++ )
            (*globDist)[i] = min( dist[i], (*globDist)[i] );
    }

//    cout<<"Total cost of the current path : "<<curr_cost<<endl;
//    cout<<"Curr thread iteration count : "<<loopCount<<endl;
}


/*
    Int this iterate, we have the following features:
    1. Multiple ants, each in their own threads
    2. Multiple iterations as compared to only 1 in Ant2
    3. Weight updating after each iteration 
*/
void AntSystem2::iterate() {

    int totVisit = 0 ;
    int i, j, n;
    vector<thread> vthread;    // vector of threads in ACO

    srand(time(NULL));

    g = new Graph;
    g->readFromFile(datasetName);   // read data from file
    n = g->getNodeCnt(); 
    
    // initialize the dist structure in the graph
    for( i=1 ; i<=n ; i++ )
       dist[i]=1000000000;      // set it to a high number
    dist[ initConf[0] ] = 0;

    cout<<"Number of nodes in graph : "<<n<<endl;

    for( j=1; j <= ANT_SYSTEM_ITERATION ; j++ ) {

        // Spawn other threads from here.
        for( i=0 ; i<THD ; i++ )
            vthread.push_back( 
                (thread(antThread, g, initConf, 
                this, &dist, j*ANT_SYSTEM_PATH_BASE )) );

        // WAIT FOR THREADS TO COMPLETE THEIR WORK

        for( i=0 ; i<THD ; i++ )
            vthread[i].join();
        vthread.clear();

        totVisit = 0 ;   // initialize this variable
        for( i=1 ; i<=n ; i++ ) 
            if( g->isnVisit(i) )
                totVisit++;
        cout<<"Number of nodes visited in iteration : "<<j<<" = "<<totVisit<<endl;
        cout<<" Visit count : "<<g->visitCnt()<<endl; 
        for( auto it = dist.begin() ; it!= dist.end() ; it++ )
            cout<<it->second<<" , ";
        cout<<endl;
    
        // Time to update RHO
        // value of rho is given in file config.h
        g->updateValueRho(); 
    }

    cout<<"-----------------------------------------------------------"<<endl;
    cout<<"FINAL Tally : "<<endl;
    cout<<" Total visited nodes by robot : "<<totVisit<<endl;
    cout<<" Visit count : "<<g->visitCnt()<<endl; 
    for( auto it = dist.begin() ; it!= dist.end() ; it++ )
        cout<<it->first<<" : "<<it->second<<endl;
    cout<<" Exiting the loop "<<endl;
}

