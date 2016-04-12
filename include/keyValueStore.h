#ifndef KEY_VALUE_STORE
#define KEY_VALUE_STORE

#include<map>
#include<array>
#include<utility>
#include<mutex>
using namespace std;


#define KEY_SZ  4   
#define INT_SZ 30

typedef array<int,KEY_SZ> CONF;     

class keyValueStore 
{
private:
    map<CONF,float > phero;
public:
    keyValueStore() {}
    float getValue(CONF key);
    void setValue(CONF key,float val);
    bool keyExist(CONF key);
    int getSize();           // returns the number of keys in container
};


#endif
