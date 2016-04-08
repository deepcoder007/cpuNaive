/*
 * genGraph.cpp
 *
 *  Created on: 21-Feb-2016
 *      Author: vibhanshu
 */

/**
    Used to generate graph for further manipulation
    The graph will be stored in file  *graph.txt*
    NOTE: Octave should be installed otherwise the program will fail
*/

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<unistd.h>
#include"commons.h"
using namespace std;

int genGraph(int x,int y)
{
    chdir("src");
    char buf[200];
    sprintf(buf,"octave --eval \"k=int32(kronecker_generator(%d,%d));k=k';dlmwrite('../data/graph.dat',k);\"",x,y);

    system(buf);
    chdir("..");
    return 0;
}


