#ifndef CONFIG_H
#define CONFIG_H

/*
    This file is is used to specify the configuration settings of the project
*/

// number of threads to run 
#define THD 8

// Number of bits to be packed in an integer
#define INT_SZ 30


// NOTE: in the values given below there is always a performance and space trade-off

// Number of hashbuckets in the unordered CONF container
#define CONF_HASH_BUCKET_COUNT 500

// Number of hashbuckets in unordered pair<int,int> container
#define PAIR_HASH_BUCKET_COUNT 500

/*
    N_VAL  : The number of nodes in the graph
    KEY_SZ : The size of the key which includes position of robot and bits
*/
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


// cost of moving a robot
#define ROBOT_COST 1

// cost of moving an obstacle
#define OBS_COST 1

// This multiplier below are multiplied to the pheromone content

// the multiplier for choosing a new node for robot
// as compared to an already visited node
#define EXPLORE_MULTI 5.0

// the multiplies for choosing a different node as 
// compared to the current node -> but it can be already visited earlier
#define EXPLORE_DIFF 3.0

// Maximum and minimum value of pheromone
// The difference between MAX and MIN is potentionally
// a deciding factor on the performance of the algorithm
#define PHERO_MAX 1000.0
#define PHERO_MIN 1.0

// THe pheromone content for binary values
#define BINARY_PHERO_MAX 1000
#define BINARY_PHERO_MIN 1

// This is the parameter RHO of the ACO
// The new phero quantity is RHO times the original quantity
// after this update
// NOTE: This is a very sensitive parameter
#define PHERO_RETENTION_RATE 0.60

// Number of iterations in the AntSystem iterate(), i'th iteration
// will be i times the base in this system
#define ANT_SYSTEM_ITERATION 10000

// The path length of the first iteration in Ant System 
#define ANT_SYSTEM_PATH_BASE 10


// The constant used while updating the value of pheromone
// keep it in the range 100-500 because intuitively 
// this is range of value will give optimal result
#define DELTA_CONST 10.0


// The probability of choosing the next node to be the one which is already visited
// NOTE: This is a very sensitive parameter in deciding the exploration path, 
//        a difference of 0.01 can make or break the results drastically
#define NEXT_NODE_VISITED_PROB 0.75

// In AntSystem5 there will be only 2 possible values of pheromone , 
// 1. PHERO_MIN
// 2. PHERO_MAX
// This is meant to be a novel approach for very large ACO systems
#define BINARY_PHERO_COUNTER 20

#endif 
