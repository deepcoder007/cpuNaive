#ifndef KEY_VALUE_STORE
#define KEY_VALUE_STORE

#include<map>
#include<array>
#include<utility>
using namespace std;

#define INT_SZ 30

#if defined N8
    #define N_VAL   8
    #define KEY_SZ  2   
#elif defined N16
    #define N_VAL   16
    #define KEY_SZ  2
#elif defined N32
    #define N_VAL   32
    #define KEY_SZ  3
#elif defined N64
    #define N_VAL   64
    #define KEY_SZ  4
#elif defined N128
    #define N_VAL   128
    #define KEY_SZ  6
#elif defined N256
    #define N_VAL   256
    #define KEY_SZ  10
#elif defined N512
    #define N_VAL   512
    #define KEY_SZ  19
#elif defined N1024
    #define N_VAL   1024
    #define KEY_SZ  36
#endif


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
