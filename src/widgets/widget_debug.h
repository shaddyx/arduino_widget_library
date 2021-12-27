#pragma once

#define NONE 0
#define ERROR 1
#define INFO 2
#define DEBUG 3

#ifndef DEBUG_LEVEL
    #define DEBUG_LEVEL NONE
#endif 

#if DEBUG_LEVEL >= INFO
    #define dbg(...) printf("%s:%d ", __FILE__, __LINE__); printf(__VA_ARGS__); printf("\n");
#else
    #define dbg(...) 
#endif

#if DEBUG_LEVEL >= DEBUG
    #define dbg_d(...) printf("%s:%d ", __FILE__, __LINE__); printf(__VA_ARGS__); printf("\n");
#else
    #define dbg_d(...) 
#endif

#if DEBUG_LEVEL >= ERROR
    #define dbg_e(...) printf("%s:%d ", __FILE__, __LINE__); printf(__VA_ARGS__); printf("\n");
#else
    #define dbg_e(...) 
#endif
    