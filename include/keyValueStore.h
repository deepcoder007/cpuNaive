#ifndef KEY_VALUE_STORE
#define KEY_VALUE_STORE

#include"config.h"
#include<array>
#include<utility>
#include<climits>
#include<algorithm>
#include<vector>

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

unsigned long hashCONF( CONF key ); 

bool equalCONF( CONF key1 , CONF key2 );

#endif


class keyValueStore 
{
private:
#if defined UNORDERED
//    unordered_map<CONF, float, function<unsigned long(CONF)>, function<bool(CONF,CONF)> >  phero[N_VAL+1];
    vector<unordered_map<CONF, 
                    float, 
                    function<unsigned long(CONF)>, 
                    function<bool(CONF,CONF)> > >  phero;
#else 
    map<CONF,float > phero[N_VAL+1];  
#endif
public:
    keyValueStore() {
#if defined UNORDERED
        phero.reserve(N_VAL+1);   // changes the capacity of the vector
        for( int i=0; i<=N_VAL ; i++ )
            phero.push_back( unordered_map<CONF,
                   float,
                   function<unsigned long(CONF)>,
                   function<bool(CONF,CONF)> > 
                   (CONF_HASH_BUCKET_COUNT,hashCONF,equalCONF) ); 
#endif
    }
    float getValue(CONF key);
    void setValue(CONF key,float val);
    bool keyExist(CONF key);
    int getSize();           // returns the number of keys in container

    // CAUTION : Call these subroutines with care
    void updateValueRho();  // update the values according to PHERO_RETENTION_RATE for all the keys in all the container
};


#endif
