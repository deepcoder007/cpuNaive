#ifndef KEY_VALUE_STORE
#define KEY_VALUE_STORE

#include"config.h"
#include<map>
#include<array>
#include<utility>
using namespace std;

typedef array<int,KEY_SZ> CONF;     

class keyValueStore 
{
private:
    map<CONF,float > phero[N_VAL+1];  
public:
    keyValueStore() {}
    float getValue(CONF key);
    void setValue(CONF key,float val);
    bool keyExist(CONF key);
    int getSize();           // returns the number of keys in container
};


#endif
