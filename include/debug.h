/*
    This is a header file defined for debuggging the source code
*/
#ifndef DEBUG_HEADER
#define DEBUG_HEADER

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include"Graph.h"
#include"binaryGraph.h"
#include"keyValueStore.h"
#include"binaryKeyValueStore.h"

// prints the configuration
void printCONF(Graph* g,CONF conf);

void printCONF(binaryGraph* g,CONF conf);
#endif
