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
#define THD 4
//#include"keyValueStore.h"
using namespace std;


// TODO: check if the case of no key can be changed
float keyValueStore::getValue(CONF key) {
    if( phero[key[0]].find(key) != phero[key[0]].end() ) {
        return phero[key[0]][key];
    } else {
        return -1.0;    // node node initialized -> in MMAS it is MAX_VALUE
    }
}


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


int keyValueStore::getSize() {
    int sz = 0;
    for(int i=1 ; i<= N_VAL ; i++ )
        sz += phero[i].size();
    return sz;
}
