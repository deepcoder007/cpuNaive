#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<unistd.h>
#include<fstream>
#include<sstream>
//#include"keyValueStore.h"
//#include"Graph.h"
//#include"debug.h"
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

void writeCONFtoFile(FILE* ptr, binaryGraph* g, CONF conf) {
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
    conf[0]=60;
    conf[1]=0;
    conf[2]=~0;
    conf[3]=~0;
    conf[4]=~0;
    conf[5]=~0;
    conf[6]=~0;
    conf[7]=~0;
    conf[8]=~0;
    conf[9]=~0;
    conf[10]=~0;
    conf[11]=~0;
    conf[12]=~0;
    conf[13]=~0;
    conf[14]=~0;
    conf[15]=~0;
    conf[16]=~0;
    conf[17]=~0;

    Ant2 rant ;
#if defined N8
    cout<<"N8"<<endl;
    rant.setDataset("graph8.dat");
#elif defined N16
    cout<<"N16"<<endl;
    rant.setDataset("graph16.dat");
#elif defined N32
    cout<<"N32"<<endl;
    rant.setDataset("graph32.dat");
#elif defined N64
    cout<<"N64"<<endl;
    rant.setDataset("graph64.dat");
#elif defined N128
    cout<<"N128"<<endl;
    rant.setDataset("graph128.dat");
#elif defined N256
    cout<<"N256"<<endl;
    rant.setDataset("graph256.dat");
#elif defined N512
    cout<<"N512"<<endl;
    rant.setDataset("graph512.dat");
#elif defined N1024
    cout<<"N1024"<<endl;
    rant.setDataset("graph1024.dat");
#endif

    rant.setInit(conf);
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
