//#include"keyValueStore.h"
#include"Algo.h"
#include"keyValueStore.h"
#include"debug.h"
#include<ctime>
#include<cstdlib>
#include<iostream>
#include<thread>
#include<utility>
#include<random>

using namespace std;

mutex Ant_dist_lock_6;

//--------------------------------------------------------------
//      The "ANT SYSTEM 2"  implementation
//      Int this version we have weight reduction after each 
//      iteration to allow for exploring newer paths
//--------------------------------------------------------------

/*
    This will be a standard ACO implementation with multiple ants but without pheromone
*/

void AntSystem4::setInit(CONF conf) {
    initConf = conf;
}


void AntSystem4::setDataset(string filename) {
    datasetName = filename;
}


/*
    Removes the configurations which are already visited
*/
set<pair<CONF,int> > AntSystem4::filterCONF(Graph* g,set<pair<CONF,int> > in) {
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
pair<CONF,int> AntSystem4::getNextConf( CONF curr, set<pair<CONF,int> >& confSet, Graph* g ) {

    vector<pair<CONF,int> > vConf1, vConf2;  // stores the list of configuration
    vector<int>             vProb1, vProb2;     // stores the probabilities  

    CONF itConf;    // stores the CONF of current it
    float currPhero;        // the pheromone content of current graph

    // loop over the confSet
    for( auto it = confSet.begin() ; it != confSet.end() ; it++ ) {

        itConf = it->first;

        // CASE 1 : this node is having a pheromone value 
        if( g->existPhero(itConf) ) 
        {
            vConf1.push_back(*it);  // push the [pair<CONF,int>] pair as it is

            currPhero = g->getPhero(itConf);

            if( itConf[0] == curr[0] ) {
                // CASE : robot position does not change
                vProb1.push_back( currPhero );
            } else if( g->isnVisit(itConf[0]) ) {
                // CASE : the position was earlier visited by robot
                //        higher premium for accessing it
                vProb1.push_back( currPhero*EXPLORE_DIFF );
            } else {
                // CASE : the position was never visited by robot
                //        highest premium for accessing it
                vProb1.push_back( currPhero*EXPLORE_DIFF*EXPLORE_MULTI );
            }
        } else {  

            // CASE 2 : if node is not having a pheromone value
            vConf2.push_back(*it);

            if( itConf[0] == curr[0] ) {
                // CASE : robot position does not change
                vProb2.push_back( PHERO_MAX );
            } else if( g->isnVisit(itConf[0]) ) {
                // CASE : the position was earlier visited by robot
                //        higher premium for accessing it
                vProb2.push_back( PHERO_MAX*EXPLORE_DIFF );
            } else {
                // CASE : the position was never visited by robot
                //        highest premium for accessing it
                vProb2.push_back( PHERO_MAX*EXPLORE_DIFF*EXPLORE_MULTI );
            }
        }
    }

    random_device rd_n;
    discrete_distribution<int> dist_n = { 1, 1 , 1, 1, 1, 1, 1, 1, 1 };
    
    // TODO : as of now CASE 1 will happen 75 % of time 
    //        better tune this whole algorithm
    if( dist_n(rd_n) != 0 && vConf1.size() > 0 ) {  

        //  NOTE: enter this loop only where there is atleast 1 visited node
        //  CASE 1 :take the already visited node
        cout<<__LINE__<<" : Choose path 1 "<<endl;
        random_device rd;
        discrete_distribution<int> dist(vProb1.begin(), vProb1.end());
        return vConf1[ dist(rd) ];

    } else {

        // CASE 2 :  randomly choose any of the unvisited node
        // print only when it is because of random number generation
        if( vConf1.size() > 0 )
            cout<<__LINE__<<" : Choose path 2 "<<endl;
        else 
            cout<<"  : Choose path 2 but because vConf1 (pheromone neighbourhood) size is 0 "<<endl;

        //  Random selection is too bad : lets do something better :D 
        //  int tmp1 = rand() % vConf2.size() ;  // decide the next node to visit

        random_device rd;
        discrete_distribution<int> dist(vProb2.begin(), vProb2.end());
        return vConf2[ dist(rd) ];
    }

}


/*
    This is to be invoked by a thread in ANT
*/
void AntSystem4::antThread(Graph* g,
                CONF initConf, AntSystem4* antobj, 
                map<int,int>* globDist,int maxloopCount) {

    set<pair<CONF,int> > confSet;    // the set of configuration nodes
    pair<CONF,int> curr;      // the current configuration
    int tmp1,tmp2;
    int n = g->getNodeCnt(); 
    int curr_cost = 0 ;         // records the cost of the current path

    // The variables below are used to save the path and other info about the path
    // to store teh per node increment of the nodes
    // these 2 variables below will be used to calculate the delta
    set<CONF> Cvisited;          // a list of visited configurations in the current path
    set<int>  Cnvisited;         // a list of nodes visited by the robot in current path
    
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

        Cvisited.insert( curr.first );   // insert this in the list of visited nodes
        Cnvisited.insert( curr.first[0] );   // insert this in the list of visited robot positions


        // CAUTION : possible point of bug
        if( !g->existPhero( curr.first) )
            g->setPhero( curr.first , PHERO_MAX );

        curr_cost += curr.second;   // add the cost of this node
        dist[ curr.first[0] ] = min( dist[curr.first[0]], curr_cost );
        g->markVisit( curr.first );        // mark the configuration visited
        confSet = filterCONF( g, g->getNeighbour( curr.first ) );  

    }

    // calculate the deltas for CONF's on this path
    // and push those deltas to the phero data structure in the graph
    {
        int nCvisited = Cvisited.size();
        int nCnvisited = Cnvisited.size();

        float deltaTmp;                  // the temporary value of delta 

        // the configuration of the previous node of the graph, in this case it is the first node
        CONF prevConf = initConf;                  

        for( auto it = Cvisited.begin() ; it != Cvisited.end() ; it++ ) {

            //      the weights will be calculated like
            //      w_(t+1) = w_(t)*( 1 + [delta] )
            // NOTE : check the value of DELTA_CONST before running this simulation
            //        This is to ensure that [delta] is not too high or low
            deltaTmp = DELTA_CONST*( g->getPhero(*it) ) ;          // the base line
            deltaTmp *= Cnvisited.size();              // the number of visited roboPos increases the value
            deltaTmp /= Cvisited.size();               // the total number of visited roboPos decrease the value
            deltaTmp *= g->getPhero(prevConf) ;        // the delta of the previous node of the graph

            // TODO : Delete this line below before going for production
            cout<<" deltaTmp/(g->getPhero(*it)) : "<<deltaTmp/g->getPhero(*it)<<endl;

            if( deltaTmp > 0 )
                g->addPhero( *it, deltaTmp );
            
            prevConf = *it ;                // update the value of prevConf to the current value
        }

    }

    // update the global distance matrix in this block
    {
        lock_guard<mutex> lck( Ant_dist_lock_6 );
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
void AntSystem4::iterate() {

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

