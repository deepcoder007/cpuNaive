#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<unordered_map>
#include<map>
#include<algorithm>
#include<array>
#include<utility>
#include<thread>
#include<chrono>
#include<unistd.h>
#include"binaryKeyValueStore.h"
//#include"binaryKeyValueStore.h"
using namespace std;


#if defined UNORDERED

unsigned long b_hashCONF( CONF key ) {
    unsigned long hash=0;
    for( int i=1 ; i<KEY_SZ ; i++ ) {
        hash = ( hash + key[i] )%INT_MAX;
    }
    return ( hash * key[0] )%INT_MAX;
}

bool b_equalCONF( CONF key1 , CONF key2 ) {
    for( int i=0 ; i<KEY_SZ ; i++ ) 
        if( key1[i] != key2[i] )
            return false;
    return true;
}

#endif


/*
    Returns the value in the container
    If value does not exist then return -1
*/
int binaryKeyValueStore::getValue(CONF key) {
    if( phero[key[0]].find(key) != phero[key[0]].end() ) {
        return phero[key[0]][key];
    } else {
        return -1;    // node node initialized -> in MMAS it is MAX_VALUE
    }
}


// The the value of key
void binaryKeyValueStore::setValue(CONF key) {
    phero[key[0]][key] = BINARY_PHERO_COUNTER;
}


// Checks if the `key` exists in the container
bool binaryKeyValueStore::keyExist(CONF key) {
    if( phero[key[0]].find(key) != phero[key[0]].end() ) {
        return true;
    } else {
        return false;
    }
}


/*
    Returns the size of this keyValue in terms of number of keys
*/
int binaryKeyValueStore::getSize() {
    int sz = 0;
    for(int i=1 ; i<= N_VAL ; i++ )
        sz += phero[i].size();
    return sz;
}


/*
    This is to implement the pheromone drying up rule in the graph
    The dry up rate is specified in the config.h file
*/
void binaryKeyValueStore::updateValueRho() {

    for(int i=0 ; i<= N_VAL ; i++ ) {
        for( auto it = phero[i].begin() ; it != phero[i].end() ; it++ ) {
            it->second--;               //  this is the case with binary pheromone storage
            if( it->second < PHERO_MIN )
                it->second = PHERO_MIN ;
        }
    }

}

// Clears the container manually to avoid memory leakage
void binaryKeyValueStore::clear() {
    for( auto it = phero.begin() ; it != phero.end() ; it++ )
        it->clear();
}

