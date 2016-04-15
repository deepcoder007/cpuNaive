#ifndef ALGO_H
#define ALGO_H
#include"keyValueStore.h"
#include"Graph.h"
#include<vector>
#include<set>
#include<string>
#include<map>

//mutex Ant_dist_lock;

// This file will contain all the algos that are to be implemented , bruteforce,random ant, ACO, etc.

/*
    The base class of all the algos
*/
class Algo {
public:
    virtual void setInit(CONF conf)=0;
    virtual void setDataset(string filename)=0;
    virtual void iterate()=0;
};

// Random ANT algo
class RandomAnt : public Algo
{
private:
    set<CONF> tabu_list;
    CONF initConf;
    Graph* g;
    string datasetName;
    
    set<pair<CONF,int> > filterCONF(set<pair<CONF,int> > in);  // filter out the visited CONFs
public:
    void setInit(CONF conf);
    void setDataset(string filename);
    void iterate();
};


// This class will run the metaheuristic algorithm in its thread
class Ant : public Algo
{
private:
    // Here there will be a global tabu_list  in graph g
   CONF initConf;
   Graph* g;
   string datasetName;

   map<int,int> dist;       // distance from home node to all the nodes

   static set<pair<CONF,int> > filterCONF(Graph* g, set<pair<CONF,int> > in);
   static void antThread(Graph* g,CONF initConf,Ant* antobj, map<int,int>* globDist);
public:
   void setInit(CONF conf);
   void setDataset(string filename);
   void iterate();  // to execute 1 step of ACO
};


/*
 This class will run the metaheuristic algorithm in its thread
 This class will run only 1 iteration in all the threads
 */
class Ant2 : public Algo
{
private:
    // Here there will be a global tabu_list  in graph g
   CONF initConf;
   Graph* g;
   string datasetName;

   map<int,int> dist;       // distance from home node to all the nodes

    // filters out the list of configuration which are already visited
   static set<pair<CONF,int> > filterCONF(Graph* g, set<pair<CONF,int> > in);
   // this is the thread in which individual ant will execute its operations
   static void antThread(Graph* g,CONF initConf,Ant2* antobj, map<int,int>* globDist, int maxloopCount );
   // returns the next configuration to be visited in graph
   static pair<CONF,int> getNextConf( CONF curr, set<pair<CONF,int> >& confSet, Graph* g ) ;  

public:
   void setInit(CONF conf);
   void setDataset(string filename);
   void iterate();  // to execute 1 step of ACO
};


/*
    In addition to ANT2, this will run multiple iterations of ANT Systme
    with a systematics weight update rule.
*/
class AntSystem : public Algo
{
private:
    // Here there will be a global tabu_list  in graph g
   CONF initConf;
   Graph* g;
   string datasetName;

   map<int,int> dist;       // distance from home node to all the nodes

    // filters out the list of configuration which are already visited
   static set<pair<CONF,int> > filterCONF(Graph* g, set<pair<CONF,int> > in);
   // this is the thread in which individual ant will execute its operations
   static void antThread(Graph* g,CONF initConf,AntSystem* antobj, map<int,int>* globDist, int maxloopCount );
   // returns the next configuration to be visited in graph
   static pair<CONF,int> getNextConf( CONF curr, set<pair<CONF,int> >& confSet, Graph* g ) ;  

public:
   void setInit(CONF conf);
   void setDataset(string filename);
   void iterate();  // to execute 1 step of ACO
};

#endif
