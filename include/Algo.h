#ifndef ALGO_H
#define ALGO_H
#include"keyValueStore.h"
#include"Graph.h"
#include<vector>
#include<set>
#include<string>
#include<map>

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


// This class will run the metaheuristic algorithm in its thread
class Ant2 : public Algo
{
private:
    // Here there will be a global tabu_list  in graph g
   CONF initConf;
   Graph* g;
   string datasetName;

   map<int,int> dist;       // distance from home node to all the nodes

   static set<pair<CONF,int> > filterCONF(Graph* g, set<pair<CONF,int> > in);
   static void antThread(Graph* g,CONF initConf,Ant2* antobj, map<int,int>* globDist, int maxloopCount );
public:
   void setInit(CONF conf);
   void setDataset(string filename);
   void iterate();  // to execute 1 step of ACO
};

#endif
