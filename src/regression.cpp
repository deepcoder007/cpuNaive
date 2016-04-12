#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<unistd.h>
#include<fstream>
#include<sstream>
#include"keyValueStore.h"
#include"Graph.h"
#include"debug.h"
#include"Algo.h"
using namespace std;

// TEST: Generate the graph and print the result
void test1() {
    cout<<"[START] : test1 "<<endl;
   chdir("src");
   char buf[200];
   sprintf(buf,"octave --eval \"k=int32(kronecker_generator(%d,%d));k=k';dlmwrite('../data/graph.dat',k);\"",4,5);
    system(buf);
    chdir("..");

    cout<<" Now reading and printing the graph file : "<<endl;
    ifstream infile("data/graph.dat");
    string line;
    while( getline(infile, line) ) {
        cout<<line<<endl;
    }
    infile.close();
    cout<<"[DONE] : test1"<<endl;
}

void writeCONFtoFile(FILE* ptr, Graph* g, CONF conf) {
   int n = g->getNodeCnt(); 
   fprintf(ptr,"%d",conf[0]);
   for(int i=1 ; i<=n ; i++ ) 
       if( g->isVacant(conf, i) )
           fprintf(ptr,",%d",i);
   fprintf(ptr,"\n");
   fflush(ptr);
}

// Testing the randomANT system -> start a single thread of a random ant
void test2()  {

    CONF conf;
    conf[0]=20;
    conf[1]=0;
    conf[2]=~0;
    conf[3]=~0;

    Ant rant ;
    rant.setInit(conf);
    rant.setDataset("graph64.dat");
    rant.iterate();

}


int main() {
    cout<<"-----------------------------------------"<<endl;
    cout<<"     Start the regression testing        "<<endl;
    cout<<"-----------------------------------------"<<endl;

    char dir[200];
    getcwd(dir,sizeof(dir));
    cout<<"Current directory : "<<dir<<endl;

    // Sequence of test cases
//    test1();
//    test1();
    test2();

    cout<<"-----------------------------------------"<<endl;
    cout<<"     Done with regression testing        "<<endl;
    cout<<"-----------------------------------------"<<endl;
    return 0;
}
