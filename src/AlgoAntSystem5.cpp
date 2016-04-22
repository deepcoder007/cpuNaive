//#include"keyValueStore.h"
#include"Algo.h"
#include"binaryKeyValueStore.h"
#include"debug.h"
#include<ctime>
#include<cstdlib>
#include<iostream>
#include<thread>
#include<utility>
#include<random>

using namespace std;

mutex Ant_dist_lock_7;

//--------------------------------------------------------------
//      The "ANT SYSTEM 5"  implementation
//      This version implements the binary version of ACO
//--------------------------------------------------------------

/*
    This will be a standard ACO implementation with multiple ants but without pheromone
*/

void AntSystem5::setInit(CONF conf) {
    initConf = conf;
}


void AntSystem5::setDataset(string filename) {
    datasetName = filename;
}


/*
    Removes the configurations which are already visited
*/
set<pair<CONF,int> > AntSystem5::filterCONF(Graph* g,set<pair<CONF,int> > in) {
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
pair<CONF,int> AntSystem5::getNextConf( CONF curr, set<pair<CONF,int> >& confSet, Graph* g ) {

    vector<pair<CONF,int> > vConf1, vConf2;  // stores the list of configuration
    vector<int>             vProb1, vProb2;     // stores the probabilities  

    CONF itConf;    // stores the CONF of current it
    float currPhero;        // the pheromone content of current graph

    // loop over the confSet
    for( auto it = confSet.begin() ; it != confSet.end() ; it++ ) {

        itConf = it->first;

        // CASE 1 : this node is having a pheromone value 
        if( g->existPhero(itConf) && g->getPhero(itConf) == BINARY_PHERO_MAX ) 
        {
            // Enter this case only when the node is discovered
            // and case is entered within BINARY_PHERO_COUNTER times number of iterations
            vConf1.push_back(*it);  // push the [pair<CONF,int>] pair as it is

        } else {  

            // CASE 2 : if node is not having a pheromone value
            vConf2.push_back(*it);

            if( itConf[0] == curr[0] ) {
                // CASE : robot position does not change
                vProb2.push_back( 1 );
            } else if( g->isnVisit(itConf[0]) ) {
                // CASE : the position was earlier visited by robot
                //        higher premium for accessing it
                vProb2.push_back( EXPLORE_DIFF );
            } else {
                // CASE : the position was never visited by robot
                //        highest premium for accessing it
                vProb2.push_back( EXPLORE_DIFF*EXPLORE_MULTI );
            }
        }
    }

    discrete_distribution<int> dist_n = { 1, 1 , 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    
    // TODO : as of now CASE 1 will happen 14/15 % of time 
    //        better tune this whole algorithm
    if( dist_n(rd_n) != 0 && vConf1.size() > 0 ) {  

        //  In AntSystem5 , do it by random selection for this case, no further sub-cases
            int tmp1 = rand() % vConf1.size() ;
            return vConf1[ tmp1 ];

    } else {

	// Make an informed choice based on the value
        discrete_distribution<int> dist(vProb2.begin(), vProb2.end());
        return vConf2[ dist(rd) ];
    }

}


/*
    This is to be invoked by a thread in ANT
*/
void AntSystem5::antThread(Graph* g,
                CONF initConf, AntSystem5* antobj, 
                map<int,int>* globDist,int maxloopCount) {

    set<pair<CONF,int> > confSet;    // the set of configuration nodes
    pair<CONF,int> curr;      // the current configuration
    int tmp1,tmp2;
    int n = g->getNodeCnt(); 
    int curr_cost = 0 ;         // records the cost of the current path

    // The variables below are used to save the path and other info about the path
    // to store teh per node increment of the nodes
    // these 2 variables below will be used to calculate the delta
    
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
        if( confSet.size() == 0 ) 
            break;

        curr = getNextConf( curr.first, confSet, g );

        g->markVisit( curr.first );        // mark the configuration visited

        // CAUTION : possible point of bug in earlier implementations
	//           This is the point where binary updation occurs
        g->setPhero( curr.first );

        curr_cost += curr.second;   // add the cost of this node
        dist[ curr.first[0] ] = min( dist[curr.first[0]], curr_cost );
        confSet = filterCONF( g, g->getNeighbour( curr.first ) );  

    }


    // update the global distance matrix in this block
    {
        lock_guard<mutex> lck( Ant_dist_lock_7 );
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
void AntSystem5::iterate() {

    int totVisit = 0 ;
    int i, j, n;
    vector<thread> vthread;    // vector of threads in ACO

    srand(time(NULL));

    g = new binaryGraph;
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

        // CAUTION: This gave me a lot of pain
        // The list of visited nodes should be cleared to start the next iteration
        g->clearVisit();
    }

    cout<<"-----------------------------------------------------------"<<endl;
    cout<<"FINAL Tally : "<<endl;
    cout<<" Total visited nodes by robot : "<<totVisit<<endl;
    cout<<" Visit count : "<<g->visitCnt()<<endl; 
    for( auto it = dist.begin() ; it!= dist.end() ; it++ )
        cout<<it->first<<" : "<<it->second<<endl;
    cout<<" Exiting the loop "<<endl;
}

