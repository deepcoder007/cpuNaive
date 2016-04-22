#ifndef ALGO_H
#define ALGO_H
//#include"keyValueStore.h"
#include"Graph.h"
#include"binaryGraph.h"
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


/*
    In addition to ant system we have pheromone update rule here
    The pheromone of the discovered nodes will get reduced with time
*/
class AntSystem2 : public Algo
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
   static void antThread(Graph* g,CONF initConf,AntSystem2* antobj, map<int,int>* globDist, int maxloopCount );
   // returns the next configuration to be visited in graph
   static pair<CONF,int> getNextConf( CONF curr, set<pair<CONF,int> >& confSet, Graph* g ) ;  

public:
   void setInit(CONF conf);
   void setDataset(string filename);
   void iterate();  // to execute 1 step of ACO
};


/*
    In addition to ant system we have pheromone update rule here
    The pheromone of the discovered nodes will get reduced with time
    In addition to AntSystem2 , the weight will also increment according to greedy mechanism
*/
class AntSystem3 : public Algo
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
   static void antThread(Graph* g,CONF initConf,AntSystem3* antobj, map<int,int>* globDist, int maxloopCount );
   // returns the next configuration to be visited in graph
   static pair<CONF,int> getNextConf( CONF curr, set<pair<CONF,int> >& confSet, Graph* g ) ;  

public:
   void setInit(CONF conf);
   void setDataset(string filename);
   void iterate();  // to execute 1 step of ACO
};


/*
    In addition to ant system we have pheromone update rule here
    The pheromone of the discovered nodes will get reduced with time
    In addition to AntSystem2 , the weight will also increment according to greedy mechanism
    Choosing next node is divided in 2 parts of ratio 9/10 ( or any ratio provided it is heavily tilted in favour of CASE 1 ) . 
        1. nodes that are already visited i.e. those that have a pheromone value
        2. nodes that are not visited i.e. they were never visited and have no pheromone value
*/
class AntSystem4 : public Algo
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
   static void antThread(Graph* g,CONF initConf,AntSystem4* antobj, map<int,int>* globDist, int maxloopCount );
   // returns the next configuration to be visited in graph
   static pair<CONF,int> getNextConf( CONF curr, set<pair<CONF,int> >& confSet, Graph* g ) ;  

public:
   void setInit(CONF conf);
   void setDataset(string filename);
   void iterate();  // to execute 1 step of ACO
};


/*
    In addition to ant system we have pheromone update rule here
    The pheromone of the discovered nodes will get reduced with time
    In addition to AntSystem2 , the weight will also increment according to greedy mechanism
    Choosing next node is divided in 2 parts of ratio 14/15 ( or any ratio provided it is heavily tilted in favour of CASE 1 ) . 
        1. nodes that are already visited i.e. those that have a pheromone value
        2. nodes that are not visited i.e. they were never visited and have no pheromone value
    In addition to AntSystem4 , we have removed some sub-cases of probability distribution 
    over the CASE 1 given above.

    NOTE: I expect that the performance will be lower in this case because for practical purpose, 
          the pheromone quantity is binary (0/1) in this case. i.e., the only thing that matters
          is if the pheromone exist or not. If this system gives better performance (i.e. binary pheromone), 
          then it will be a miracle and breakthrought, because it will change the dynamics of the system. :)
          We can optimize this class a lot in that case
            
          The pheromone rule can work like this :
          1. By default pheromone value of unvisited node is PHERO_MAX
          2. When the node is first visited, the PHEROmone value is activated and phero value is set to 1.
          3. in some k(define it in config.h) iterations  that pheromone value is again set to 0.
          4. the value k is counted from the last time the particular configuration is visited, i.e.: k is reset to 0 when 
             we visit the node

          practically current update rules are working similar but they are not optimized for speed and hence taking a lot of time.

*/
class AntSystem5 : public Algo
{
private:
    // Here there will be a global tabu_list  in graph g
   CONF initConf;
   binaryGraph* g;
   string datasetName;
//   random_device rd, rd_n;

   map<int,int> dist;       // distance from home node to all the nodes

    // filters out the list of configuration which are already visited
   static set<pair<CONF,int> > filterCONF(binaryGraph* g, set<pair<CONF,int> > in);
   // this is the thread in which individual ant will execute its operations
   static void antThread(binaryGraph* g,CONF initConf,AntSystem5* antobj, map<int,int>* globDist, int maxloopCount );
   // returns the next configuration to be visited in graph
   static pair<CONF,int> getNextConf( CONF curr, set<pair<CONF,int> >& confSet, binaryGraph* g ) ;  

public:
   void setInit(CONF conf);
   void setDataset(string filename);
   void iterate();  // to execute 1 step of ACO
};


#endif
