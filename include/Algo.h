#ifndef ALGO_H
#define ALGO_H
#include"keyValueStore.h"
#include"Graph.h"
#include<vector>
#include<set>


// This class will run the metaheuristic algorithm in its thread
class Ant
{
private:
   set<CONF> tabu_list;     // the tabu list for this ant 
   Graph* g;
public:
   void iterate();  // to execute 1 step of ACO
};

#endif
