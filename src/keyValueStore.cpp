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
#include"keyValueStore.h"
//#include"keyValueStore.h"
using namespace std;


#if defined UNORDERED

unsigned long hashCONF( CONF key ) {
    unsigned long hash=0;
    for( int i=1 ; i<KEY_SZ ; i++ ) {
        hash = ( hash + key[i] )%INT_MAX;
    }
    return ( hash * key[0] )%INT_MAX;
}

bool equalCONF( CONF key1 , CONF key2 ) {
    for( int i=0 ; i<KEY_SZ ; i++ ) 
        if( key1[i] != key2[i] )
            return false;
    return true;
}

#endif


// TODO: check if the case of no key can be changed
float keyValueStore::getValue(CONF key) {
    if( phero[key[0]].find(key) != phero[key[0]].end() ) {
        return phero[key[0]][key];
    } else {
        return -1.0;    // node node initialized -> in MMAS it is MAX_VALUE
    }
}


// The the value of key
void keyValueStore::setValue(CONF key,float val) {
    phero[key[0]][key]=val;
}


bool keyValueStore::keyExist(CONF key) {
    if( phero[key[0]].find(key) != phero[key[0]].end() ) {
        return true;
    } else {
        return false;
    }
}


/*
    Returns the size of this keyValue in terms of number of keys
*/
int keyValueStore::getSize() {
    int sz = 0;
    for(int i=1 ; i<= N_VAL ; i++ )
        sz += phero[i].size();
    return sz;
}


/*
    This is to implement the pheromone drying up rule in the graph
    The dry up rate is specified in the config.h file
*/
void keyValueStore::updateValueRho() {

    for(int i=0 ; i<= N_VAL ; i++ ) {
        for( auto it = phero[i].begin() ; it != phero[i].end() ; it++ ) {
            it->second = it->second * PHERO_RETENTION_RATE ;
            if( it->second < PHERO_MIN )
                it->second = PHERO_MIN ;
        }
    }

}

// Increments the value of key
void keyValueStore::addValue(CONF key,float val) {
    if( phero[key[0]].find(key) != phero[key[0]].end() )
        phero[key[0]][key] += val;
    else 
        phero[key[0]][key] = val ;          // if key does not already exist , simply initialize it
}


// Clears the container manually to avoid memory leakage
void keyValueStore::clear() {
    for( auto it = phero.begin() ; it != phero.end() ; it++ )
        it->clear();
}

