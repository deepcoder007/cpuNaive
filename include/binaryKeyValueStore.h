#ifndef BINARY_KEY_VALUE_STORE
#define BINARY_KEY_VALUE_STORE

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

unsigned long b_hashCONF( CONF key ); 

bool b_equalCONF( CONF key1 , CONF key2 );

#endif


class binaryKeyValueStore 
{
private:
#if defined UNORDERED
//    unordered_map<CONF, float, function<unsigned long(CONF)>, function<bool(CONF,CONF)> >  phero[N_VAL+1];
    vector<unordered_map<CONF, 
                    int, 
                    function<unsigned long(CONF)>, 
                    function<bool(CONF,CONF)> > >  phero;
#else 
    map<CONF,int > phero[N_VAL+1];  
#endif
public:
    binaryKeyValueStore() {
#if defined UNORDERED
        phero.reserve(N_VAL+1);   // changes the capacity of the vector
        for( int i=0; i<=N_VAL ; i++ )
            phero.push_back( unordered_map<CONF,
                   int,
                   function<unsigned long(CONF)>,
                   function<bool(CONF,CONF)> > 
                   (CONF_HASH_BUCKET_COUNT,b_hashCONF,b_equalCONF) ); 
#endif
    }
    int getValue(CONF key);
    void setValue(CONF key);  // set this value for 'BINARY_PHERO_COUNTER' number of steps
    bool keyExist(CONF key);
    int getSize();           // returns the number of keys in container

    // CAUTION : Call these subroutines with care
    void updateValueRho();  // decrement the counter of all the values

    // CAUTION: The clear() subroutine is not threadsafe and hence should be called with care
    void clear();
};


#endif
