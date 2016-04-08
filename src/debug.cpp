#include"debug.h"

void printCONF(Graph* g,CONF conf) {
    int n = g->getNodeCnt();    
    cout<<" CONF :: ";
    cout<<" Robot : "<<conf[0]<<" :: ";
    cout<<" Vacant: ";
    int i;
    for( i = 1 ; i<=n ; i++ ) 
        if( g->isVacant(conf, i ) ) 
            cout<<i<<",";
    cout<<endl;
}




