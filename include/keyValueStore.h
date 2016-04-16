#ifndef KEY_VALUE_STORE
#define KEY_VALUE_STORE

#include"config.h"
#include<array>
#include<utility>
#include<climits>

#if defined UNORDERED
    #include<unordered_map> 
    #include<functional>
#else
    #include<map>
#endif

using namespace std;

typedef array<int,KEY_SZ> CONF;     

// Otherwise this section of code is not required
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


class keyValueStore 
{
private:
#if defined UNORDERED
    unordered_map<CONF,
                float, 
                function<unsigned long(CONF)>, 
                function<bool(CONF,CONF)> > 
                phero(CONF_HASH_BUCKET_COUNT, hashCONF, equalCONF )[N_VAL+1];
#else 
    map<CONF,float > phero[N_VAL+1];  
#endif
public:
    keyValueStore() {}
    float getValue(CONF key);
    void setValue(CONF key,float val);
    bool keyExist(CONF key);
    int getSize();           // returns the number of keys in container

    // CAUTION : Call these subroutines with care
    void updateValueRho();  // update the values according to PHERO_RETENTION_RATE for all the keys in all the container
};


#endif
