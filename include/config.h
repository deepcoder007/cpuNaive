#ifndef CONFIG_H
#define CONFIG_H

/*
    This file is is used to specify the configuration settings of the project
*/

// number of threads to run 
#define THD 8

// Number of bits to be packed in an integer
#define INT_SZ 30

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
#define PHERO_MAX 100.0
#define PHERO_MIN 1.0

// This is the parameter RHO of the ACO
#define PHERO_RETENTION_RATE 0.90

#endif 